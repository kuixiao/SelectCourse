package controller

import (
	"../db"
	"../model"
	"fmt"
	"github.com/ant0ine/go-json-rest/rest"
	"log"
	"strconv"
	"time"
)

type WebController struct {
}

type login struct {
	UserName string
	Pwd      string
}

// 学生注册
func (webController *WebController) StudentRegister(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("webController.go:StudentRegister()")

	var (
		err      error
		register model.Tb_student
		baseGorm db.BaseGorm
		count int
	)
	returnJson := make(map[string]interface{})

	// r.Body 解析
	err = r.DecodeJsonPayload(&register)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	_, count,_=baseGorm.QueryUserInfo("")
	temp := "00000" + strconv.Itoa(count+1)
	register.Sno = temp[len(temp) - 6 :]

	//判断编号是否存在
	_, count,_=baseGorm.QueryUserInfo(register.Sno)
	if count>0 {
		returnJson["code"] = 2
		returnJson["msg"] = "The number is already existed!"
		panic(w.WriteJson(returnJson))
		return
	}

	tx := baseGorm.GetDB().Begin()

	// 向学生信息表插入注册用户
	err = db.CreateStudent(tx, register)
	if err != nil {
		returnJson["code"] = 1
		returnJson["msg"] = "register fail!"
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}
	tx.Commit()
	returnJson["code"] = 0
	returnJson["msg"] = "register success!"
	w.WriteJson(returnJson)
}

// 教师注册
func (webController *WebController) TeacherRegister(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("webController.go:TeacherRegister()")


	var (
		err      error
		register model.Tb_teacher
		baseGorm db.BaseGorm
		count int
	)
	returnJson := make(map[string]interface{})

	err = r.DecodeJsonPayload(&register)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}
	_, count,_=baseGorm.QueryUserInfo("")
	temp := "00000" + strconv.Itoa(count+1)
	register.Tno = temp[len(temp) - 6 :]

	//判断编号是否存在
	_, count,_=baseGorm.QueryUserInfo(register.Tno)
	if count>0 {
		returnJson["code"] = 2
		returnJson["msg"] = "The ID is already existed!"
		panic(w.WriteJson(returnJson))
		return
	}
	tx := baseGorm.GetDB().Begin()

	// 向教师表插入用户
	err = db.CreateTeacher(tx, register)
	if err != nil {
		returnJson["code"] = 1
		returnJson["msg"] = "register fail!"
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}
	tx.Commit()
	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	w.WriteJson(returnJson)
}

// 用户登录
func (webController *WebController) UserLogin(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("webController.go:StudentLogin()")

	var (
		err      error
		login    login //仅包含用户名与密码
		userInfo model.Tb_user
		baseGorm *db.BaseGorm
		count    int
	)
	returnJson := make(map[string]interface{})  // 包含 returnJson["code"] returnJson["msg"] returnJson["token"]
	err = r.DecodeJsonPayload(&login)// 解析json请求
	if err != nil { // 解析出错
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	tx := baseGorm.GetDB().Begin()
	userInfo, count, err = baseGorm.QueryUserInForLogin(login.UserName, login.Pwd)
	if count == 0 { // 用户名或密码不正确
		returnJson["code"] = 2
		returnJson["msg"] = "Account and password do not match!"
		panic(w.WriteJson(returnJson))
		return
	}
	if err != nil { // 查询出错
		returnJson["code"] = 1
		returnJson["msg"] = "query data from user_info by username and pwd fail!"
		panic(w.WriteJson(returnJson))
		return
	}
	// 数据库更新令牌与登录时间
	fmt.Println("id:",userInfo.Id)
	userInfo.Token = strconv.FormatInt(time.Now().Unix(), 10) + userInfo.Id
	userInfo.Deadline = strconv.FormatInt(time.Now().Unix()+(1*1*3600), 10)
	err = baseGorm.UpdateUserTable(tx, userInfo)
	if err != nil {
		returnJson["code"] = 1
		returnJson["msg"] = "update loginUserInfo fail!"
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}
	tx.Commit()

	returnJson["code"] = 0
	returnJson["msg"] = "login success!"
	returnJson["token"] = userInfo.Token
	w.WriteJson(returnJson)
}

// 用户注销
func (webController *WebController) UserLoginout(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("webController.go:UserLoginout()")
	var (
		err      error
		userInfo model.Tb_user
		baseGorm *db.BaseGorm
	)
	returnJson := make(map[string]interface{})
	id := r.PathParam("id")

	// 更新用户登录表 即用户注销删除令牌信息与超时信息
	tx := baseGorm.GetDB().Begin()
	userInfo, _, _ = baseGorm.QueryUserInfo(id)
	userInfo.Token = ""
	userInfo.Deadline = ""

	err = baseGorm.UpdateUserTable(tx, userInfo)
	if err != nil {
		returnJson["code"] = 1
		returnJson["msg"] = "update user_info fail!"
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}
	tx.Commit()

	returnJson["code"] = 0
	returnJson["msg"] = "loginout success!"
	w.WriteJson(returnJson)
}




