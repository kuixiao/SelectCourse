package main

import (
	"./common"
	"./controller"
	"./db"
	"fmt"
	"github.com/ant0ine/go-json-rest/rest"
	"log"
	"net/http"
)

func main() {
	new(db.BaseGorm).InitDB()
	api := rest.NewApi()
	api.Use(rest.DefaultDevStack...)

	// 使用第三方中间件AuthTokenMiddleware，对token进行验证
	// AuthTokenMiddleware是一个结构体
	tokenAuthMiddleware := &common.AuthTokenMiddleware{
		Realm: "jwt auth", //域名

		// 根据令牌对用户进行身份验证的回调函数。
		// 成功时f返回deadline，失败时返回空字符串。
		Authenticator: func(token string) string {
			var baseGorm *db.BaseGorm
			fmt.Println("查询令牌是否存在")
			userInfo, count, err := baseGorm.QueryUseInfoByToken(token)
			if err != nil || count == 0 { // 查询错误或令牌不存在
				fmt.Println("查询错误或令牌不存在")
				return ""
			} else {
				fmt.Println("令牌存在")
				return userInfo.Deadline
			}
		},

		// 仅在授权成功后调用
		// 成功时必须返回true，失败时必须返回false。可选，默认为成功
		Authorizer: nil,
	}

	//使用go-json-rest自带的中间件IfMiddleware筛选判断
	//因为login、register接口在使用时没有token，不能经过AuthTokenMiddleware中间件验证，因此需要将其过滤
	//api.Use()将一个或多个中间件推送到API对象中维护的中间件的堆栈中
	api.Use(&rest.IfMiddleware{
		Condition: func(request *rest.Request) bool {
			var arr = []string{
				"/login","/register/teacher","/register/student",
			}
			for _, item := range arr {
				if item == request.URL.Path {
					fmt.Println("return false")
					return false
				}
			}
			return true
		},
		IfTrue: tokenAuthMiddleware,
	})

	router, err := rest.MakeRouter(
		// 注册、登录、注销
		rest.Post("/register/teacher",new (controller.WebController).TeacherRegister),	// 已写 已验证
		rest.Post("/register/student",new (controller.WebController).StudentRegister),	// 已写 已验证
		rest.Post("/login",new (controller.WebController).UserLogin),			// 已写 已验证
		rest.Put("/loginout/:id",new (controller.WebController).UserLoginout),	// 已写 已验证

		// 修改用户本人信息	id为用户id(包括学生、教师、系主任)
		rest.Put("/update/:id",new (controller.UserController).UpdateUser),		// 已写 已验证

		// 学生增加选课信息
		rest.Post("/users/add/stucourse/:id",new (controller.UserController).AddStuCourse), // 已写 已验证
		// 学生查询个人信息
		rest.Get("/users/student/:id", new (controller.UserController).QueryStudent),	// 已写 已验证
		// 学生查询选课课堂信息
		rest.Get("/users/student/allclass/:id", new (controller.UserController).QueryAllStuClass),	// 已写 未验证
		// 学生查询个人选课结果信息
		rest.Get("/users/student/myclass/:id", new (controller.UserController).QueryPersonalStuClass),	// 已写



		rest.Get("/users/course/:id", new (controller.UserController).QueryCourse),		// 已写 已验证
		// 教师查询个人信息
		rest.Get("/users/teacher/:id", new (controller.UserController).QueryTeacher),	// 已写 已验证
		// 教师查询个人所有课堂信息
		rest.Get("/users/teacher/myclass/:id", new (controller.UserController).QueryPersonalTeaClass),	// 已写 已验证
		// 教师查询某课堂所有选课学生信息
		rest.Get("/users/teacher/mystudent/:id/:Cnumber", new (controller.UserController).QueryAllStudentOfClass),	// 已写 已验证
		// 教师修改课堂信息
		rest.Put("/update/classinfo/:id",new (controller.UserController).UpdateClass), // 已写 已验证

		// 系主任查询个人信息
		rest.Get("/users/dean/:id", new (controller.UserController).QueryDean),			// 已写 已验证
		// 系主任查询所有学生信息
		rest.Get("/users/allstudent/:id", new (controller.UserController).QueryAllStudent),	// 已写 已验证
		// 系主任查询所有教师信息
		rest.Get("/users/allteacher/:id", new (controller.UserController).QueryAllTeacher),	// 已写 已验证
		// 系主任查询所有课程信息
		rest.Get("/users/allcourse/:id", new (controller.UserController).QueryAllCourse),	// 已写 已验证
		// 系主任查询所有课程信息
		rest.Get("/users/allclass/:id", new (controller.UserController).QueryAllClass),		// 已写 已验证


		// 系主任增加排课信息 可删
		rest.Post("/users/add/teacourse/:id",new (controller.UserController).AddTeaCourse),	// 已写 未验证
		// 系主任增加课程信息
		rest.Post("/users/add/courseinfo/:id",new (controller.UserController).AddCourse),	// 已写 已验证
		// 系主任增加课堂信息
		rest.Post("/users/add/classinfo/:id",new (controller.UserController).AddClass),		// 已写
		// 系主任增加教师信息
		rest.Post("/users/add/teacher/:id",new (controller.WebController).TeacherRegister),	// 已写
		// 系主任增加学生信息
		rest.Post("/users/add/student/:id",new (controller.WebController).StudentRegister),	// 已写

		// 系主任修改课程信息
		rest.Put("/users/update/course/:id",new (controller.UserController).UpdateCourse),	// 已写 已验证
		// 系主任修改课堂信息
		rest.Put("/users/update/class/:id",new (controller.UserController).UpdateClass),	// 已写
		// 系主任修改教师信息
		rest.Put("/users/update/teacher/:id",new (controller.UserController).UpdateTeacher),// 已写
		// 系主任修改学生信息
		rest.Put("/users/update/student/:id",new (controller.UserController).UpdateStudent),// 已写

		// 系主任删除课程信息
		rest.Delete("/users/delete/course/:id/:Cno",new (controller.UserController).DeleteCourse),	// 已写 已验证
		// 系主任删除课堂信息
		rest.Delete("/users/delete/class/:id/:Cnumber",new (controller.UserController).DeleteClass),// 已写 已验证
		// 系主任删除教师信息
		rest.Delete("/users/delete/teacher/:id/:Tno",new (controller.UserController).DeleteTeacher),// 已写 已验证
		// 系主任删除学生信息
		rest.Delete("/users/delete/student/:id/:Sno",new (controller.UserController).DeleteStudent),// 已写 已验证

	)
	if err != nil {
		log.Fatal(err)
	}
	api.SetApp(router)
	http.Handle("/api/", http.StripPrefix("/api", api.MakeHandler()))
	log.Fatal(http.ListenAndServe(":8080", nil))
	fmt.Println("auth")
}
