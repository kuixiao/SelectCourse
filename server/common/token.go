package common

import (
	"crypto/md5"
	"crypto/rand"
	"crypto/subtle"
	"encoding/base64"
	"errors"
	"fmt"
	"github.com/ant0ine/go-json-rest/rest"
	"log"
	"net/http"
	"strings"
	"time"
	"strconv"
)

var tokenEntropy = 32

// AuthTokenMiddleware provides a Token Auth implementation. On success, the wrapped middleware
// is called, and the userID is made available as request.Env["REMOTE_USER"].(string)
type AuthTokenMiddleware struct {
	// Realm name to display to the user. Required.
	Realm string

	// Callback function that should perform the authentication of the user based on token.
	// Must return userID as string on success, empty string on failure. Required.
	// The returned userID is normally the primary key for your user record.
	Authenticator func(token string) string

	// Callback function that should perform the authorization of the authenticated user.
	// Must return true on success, false on failure. Optional, defaults to success.
	// Called only after an authentication success.
	Authorizer func(request *rest.Request) bool
}

// MiddlewareFunc makes AuthTokenMiddleware implement the Middleware interface.
func (mw *AuthTokenMiddleware) MiddlewareFunc(handler rest.HandlerFunc) rest.HandlerFunc {
	fmt.Println("token.go:MiddlewareFunc")
	if mw.Realm == "" {
		log.Fatal("Realm is required")
	}

	if mw.Authenticator == nil {
		log.Fatal("Authenticator is required")
	}


	if mw.Authorizer == nil {
		mw.Authorizer = func(request *rest.Request) bool {
			return true
		}
	}
	return func(writer rest.ResponseWriter, request *rest.Request) {
		authHeader := request.Header.Get("Authorization") // 提取通信指令
		// Authorization header was not provided
		if authHeader == "" {
			mw.unauthorized(writer)
			return
		}

		// Authenticator()验证令牌存在并返回deadline
		deadline := mw.Authenticator(authHeader)
		fmt.Println("deadline:", deadline)
		// The token didn't map to a user, it's most likely either invalid or expired
		if deadline == "" {
			mw.unauthorized(writer)
			return
		}
		deadlineInt,_:=strconv.ParseInt(deadline,10,64)
        if time.Now().Unix() > deadlineInt{
			mw.requestTimeout(writer)
        	return
		}

		// The user's token was valid, but they're not authorized for the current request
		if !mw.Authorizer(request) {
			mw.unauthorized(writer)
			return
		}
		fmt.Println("handler(writer, request)")
		handler(writer, request)
	}
}

// 令牌不存在或令牌已失效
func (mw *AuthTokenMiddleware) unauthorized(writer rest.ResponseWriter) {
	fmt.Println("token.go:unauthorized")
	writer.Header().Set("WWW-Authenticate", "Token realm="+mw.Realm)
	rest.Error(writer, "Request Timeout", http.StatusUnauthorized)
}

// 连接超时返回超时提示
func (mw *AuthTokenMiddleware) requestTimeout(writer rest.ResponseWriter) {
	fmt.Println("token.go:requestTimeout")
	writer.Header().Set("WWW-Authenticate", "Token realm="+mw.Realm)
	rest.Error(writer, "Request Timeout", http.StatusRequestTimeout)
}

// 从json的Header提取Token
func decodeAuthHeader(header string) (string, error) {
	fmt.Println("token.go:decodeAuthHeader")
	parts := strings.SplitN(header, " ", 2)
	if !(len(parts) == 2 && parts[0] == "Token") {
		return "", errors.New("Invalid Authorization header")
	}
	_, err := base64.URLEncoding.DecodeString(parts[1])
	if err != nil {
		return "", errors.New("Token encoding not valid")
	}
	return string(parts[1]), nil
}

// 从json的Header提取Authorization的value送至decodeAuthHeader()
func Token(request *rest.Request) (string, error) {
	fmt.Println("token.go:Token")
	authHeader := request.Header.Get("Authorization")
	return decodeAuthHeader(authHeader)
}
















// New generates a new random token
func New() (string, error) {
	fmt.Println("token.go:New()")
	bytes := make([]byte, tokenEntropy)
	_, err := rand.Read(bytes[:cap(bytes)])
	if err != nil {
		return "", err
	}
	return base64.URLEncoding.EncodeToString(bytes), nil
}

// Equal does constant-time XOR comparison of two tokens
func Equal(a, b string) bool {
	fmt.Println("token.go:Equal")
	return subtle.ConstantTimeCompare([]byte(a), []byte(b)) == 1
}

// Hash applies a simple MD5 hash over a token, making it safe to store
func Hash(token string) string {
	fmt.Println("token.go:Hash")
	hashed := md5.Sum([]byte(token))
	return base64.URLEncoding.EncodeToString(hashed[:])
}



