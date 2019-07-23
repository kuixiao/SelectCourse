package controller

import (
	"../db"
	"../model"
	"../tools"
	_ "bufio"
	"encoding/json"
	"fmt"
	"github.com/ant0ine/go-json-rest/rest"
	_ "github.com/astaxie/beego/validation"
	"github.com/jinzhu/gorm"
	"log"
	"strconv"
)

type UserController struct {
}

func checkError(err error, code int, msg string, ) (returnJson map[string]interface{}, err1 error){
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = code
		returnJson["msg"] = err.Error()
		err1 = err
		return returnJson, err1
	}
	return returnJson, nil
}

func getIdentityById(userId string) (identity int, err error){
	var(
		baseGorm    *db.BaseGorm
		userInfo	model.Tb_user
		count		int
	)
	userInfo, count, err = baseGorm.QueryUserInfo(userId)
	if count == 0 || err != nil{
		return -1, err
	}
	identity = userInfo.Identity
	return identity, nil
}

// 查询用户信息
func (userController *UserController) QueryUser(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryUser()")
	returnJson := make(map[string]interface{})

	//解析获取数据
	id := r.PathParam("id")

	//通过gorm操作数据库
	baseGorm:=db.BaseGorm{}
	userInfo, err := baseGorm.QueryStudentInfo(id)
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "query userInfo success!"
	returnJson["user"] = userInfo
	w.WriteJson(returnJson)
}

// 查询学生信息
func (userController *UserController) QueryStudent(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryStudent()")
	returnJson := make(map[string]interface{})

	//解析获取数据
	id := r.PathParam("id")

	//通过gorm操作数据库
	baseGorm:=db.BaseGorm{}
	userInfo, err := baseGorm.QueryStudentInfo(id)
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "query userInfo success!"
	returnJson["data"] = userInfo
	w.WriteJson(returnJson)
}

// 查询教师信息
func (userController *UserController) QueryTeacher(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryTeacher()")
	returnJson := make(map[string]interface{})

	//解析获取数据
	id := r.PathParam("id")

	//通过gorm操作数据库
	baseGorm:=db.BaseGorm{}
	userInfo, err := baseGorm.QueryTeacherInfo(id)
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "query userInfo success!"
	returnJson["data"] = userInfo
	w.WriteJson(returnJson)
}

// 查询系主任信息
func (userController *UserController) QueryDean(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryDean()")
	returnJson := make(map[string]interface{})

	//解析获取数据
	id := r.PathParam("id")

	//通过gorm操作数据库
	baseGorm:=db.BaseGorm{}
	userInfo, err := baseGorm.QueryDeanInfo(id)
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	returnJson["data"] = userInfo
	w.WriteJson(returnJson)
}

// 查询课程信息
func (userController *UserController) QueryCourse(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryCourse()")
	returnJson := make(map[string]interface{})

	//解析获取数据
	id := r.PathParam("id")


	//通过gorm操作数据库
	baseGorm:=db.BaseGorm{}
	courseInfo, _, err := baseGorm.QueryCourseInfo(id)
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "query courseInfo success!"
	returnJson["data"] = courseInfo
	w.WriteJson(returnJson)
}

// 查询所有学生信息
func (userController *UserController) QueryAllStudent(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryAllStendent()")
	returnJson := make(map[string]interface{})
	var (
		err               	error
		baseGorm          	*db.BaseGorm
		allStudentInfo		[]model.Tb_student
	)
	//通过gorm操作数据库
	allStudentInfo, err = baseGorm.QueryAllStudentInfo()
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "query userInfo success!"
	returnJson["data"] = allStudentInfo
	w.WriteJson(returnJson)
}

// 查询所有教师信息
func (userController *UserController) QueryAllTeacher(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryAllTeacher()")
	returnJson := make(map[string]interface{})
	var (
		err               	error
		baseGorm          	*db.BaseGorm
		allTeacherInfo		[]model.Tb_teacher
	)
	//通过gorm操作数据库
	allTeacherInfo, err = baseGorm.QueryAllTeacherInfo()
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "query all teachertInfo success!"
	returnJson["data"] = allTeacherInfo
	w.WriteJson(returnJson)
}

// 查询所有课程信息
func (userController *UserController) QueryAllCourse(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryAllCourse()")
	returnJson := make(map[string]interface{})
	var (
		err               	error
		baseGorm          	*db.BaseGorm
		allCourseInfo		[]model.Tb_course
	)
	//通过gorm操作数据库
	allCourseInfo, err = baseGorm.QueryAllCourseInfo()
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "query all all courseInfo success!"
	returnJson["data"] = allCourseInfo
	w.WriteJson(returnJson)
}

// 查询所有课堂信息
func (userController *UserController) QueryAllClass(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryAllClass()")
	returnJson := make(map[string]interface{})
	var (
		err               	error
		baseGorm          	*db.BaseGorm
		allClassInfo		[]model.Allclassinfo
	)
	//通过gorm操作数据库
	allClassInfo, err = baseGorm.QueryAllClassInfo()
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "query all all courseInfo success!"
	returnJson["data"] = allClassInfo
	w.WriteJson(returnJson)
}


// 查询某课堂所有学生信息
func (userController *UserController) QueryAllStudentOfClass(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryAllStudentOfClass()")
	returnJson := make(map[string]interface{})
	var (
		err               	error
		baseGorm          	*db.BaseGorm
		Cnumber				string
		allStudentInfo		[]model.Studentofclass
	)
	Cnumber = r.PathParam("Cnumber")
	//通过gorm操作数据库
	allStudentInfo, err = baseGorm.QueryAllStudentInfoOfClass(Cnumber)
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	returnJson["data"] = allStudentInfo
	w.WriteJson(returnJson)
}

// 查询用于学生选课的所有课堂信息
func (userController *UserController) QueryAllStuClass(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryPersonalClass()")
	returnJson := make(map[string]interface{})
	var (
		err               	error
		baseGorm          	*db.BaseGorm
		stuclassInfo	[]model.Stuclass
	)
	//通过gorm操作数据库
	stuclassInfo, err = baseGorm.QueryStuClassInfo()
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	returnJson["data"] = stuclassInfo
	w.WriteJson(returnJson)
}

// 查询某教师所有课堂信息
func (userController *UserController) QueryPersonalTeaClass(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryPersonalClass()")
	returnJson := make(map[string]interface{})
	var (
		err               	error
		baseGorm          	*db.BaseGorm
		userId				string
		personalClassInfo	[]model.Personalclass
	)
	userId = r.PathParam("id")
	//通过gorm操作数据库
	personalClassInfo, err = baseGorm.QueryTeaPersonalClassInfo(userId)
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	returnJson["data"] = personalClassInfo
	w.WriteJson(returnJson)
}

// 查询某学生选课结果信息
func (userController *UserController) QueryPersonalStuClass(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:QueryPersonalStuClass()")
	returnJson := make(map[string]interface{})
	var (
		err               	error
		baseGorm          	*db.BaseGorm
		userId				string
		personalClassInfo	[]model.Stupersonalclass
	)
	userId = r.PathParam("id")
	//通过gorm操作数据库
	personalClassInfo, err = baseGorm.QueryStuPersonalClassInfo(userId)
	if err != nil {
		log.Fatal(err)
		//操作失败返回结果
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	//操作成功返回结果
	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	returnJson["data"] = personalClassInfo
	w.WriteJson(returnJson)
}

// 修改密码
func updatePwdInUserTable(tx *gorm.DB, userInfo model.Tb_user, pwd string) (err error){
	fmt.Println("userContriller.go:updatePwdInUserTable()", pwd)
	if len(pwd) != 0 {
		var baseGorm    *db.BaseGorm
		userInfo.Pwd = pwd
		err = baseGorm.UpdateUserTable(tx, userInfo)
		return err
	}
	return nil
}

// 用户修改个人信息 包括 学生、教师、系主任
func (userController *UserController) UpdateUser(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:UpdateUser()")
	var (
		userInfo	model.Tb_user
		err         error
		baseGorm    *db.BaseGorm
		count		int
		token		string
		identity	int
		userid		string

		)

	// 根据通信令牌验证用户并获取其id
	returnJson := make(map[string]interface{})
	token = r.Header.Get("Authorization")
	userInfo, count, err =baseGorm.QueryUseInfoByToken(token)
	if count ==0 {
		returnJson["code"] = 1
		returnJson["msg"] = "the token is not exist!"
		panic(w.WriteJson(returnJson))
		return
	}
	if err != nil{
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	identity = userInfo.Identity
	userid = userInfo.Id

	//开启事务
	tx := baseGorm.GetDB().Begin()
	switch identity {
	case 0:		//更新学生信息
		// 获取新的完整的学生信息
		var oldStudentInfo,newStudentInfo  model.Tb_student
		oldStudentInfo, err = baseGorm.QueryStudentInfo(userid)
		err = r.DecodeJsonPayload(&newStudentInfo)
		if err != nil{
			log.Fatal(err)
			returnJson["code"] = 1
			returnJson["msg"] = err.Error()
			panic(w.WriteJson(returnJson))
			return
		}
		newUserInfo := tools.StructToMapViaJson(newStudentInfo)
		updateInfo := tools.StructToMapViaJson(oldStudentInfo)
		for key, value := range newUserInfo {
			if len(value) != 0{
				updateInfo[key] = value
			}
		}

		// 可能更新密码
		err  = updatePwdInUserTable(tx, userInfo, newUserInfo["Spassword"])
		if err != nil {
			log.Fatal(err)
			returnJson["code"] = 1
			returnJson["msg"] = err.Error()
			panic(w.WriteJson(returnJson))
			tx.Rollback()
			return
		}

		// 执行更新操作
		j, err := json.Marshal(updateInfo)
		json.Unmarshal(j, &newStudentInfo)
		err = baseGorm.UpdateStudentInfo(tx, newStudentInfo)
		if err != nil {
			log.Fatal(err)
			returnJson["code"] = 1
			returnJson["msg"] = err.Error()
			panic(w.WriteJson(returnJson))
			tx.Rollback()
			return
		}

		break
	case 1:		//更新教师信息
		// 获取新的完整的教师信息
		fmt.Println("更新教师信息")
		var oldTeacherInfo,newTeacherInfo  model.Tb_teacher
		oldTeacherInfo, err = baseGorm.QueryTeacherInfo(userid)

		err = r.DecodeJsonPayload(&newTeacherInfo)
		if err != nil{
			log.Fatal(err)
			returnJson["code"] = 1
			returnJson["msg"] = err.Error()
			panic(w.WriteJson(returnJson))
			return
		}
		newUserInfo := tools.StructToMapViaJson(newTeacherInfo)
		updateInfo := tools.StructToMapViaJson(oldTeacherInfo)
		for key, value := range newUserInfo {
			if len(value) != 0{
				updateInfo[key] = value
			}
		}

		// 可能更新密码
		err  = updatePwdInUserTable(tx, userInfo, newUserInfo["Tpassword"])
		if err != nil {
			log.Fatal(err)
			returnJson["code"] = 1
			returnJson["msg"] = err.Error()
			panic(w.WriteJson(returnJson))
			tx.Rollback()
			return
		}

		// 执行更新操作
		j, err := json.Marshal(updateInfo)
		json.Unmarshal(j, &newTeacherInfo)
		err = baseGorm.UpdateTeacherInfo(tx, newTeacherInfo)
		if err != nil {
			log.Fatal(err)
			returnJson["code"] = 1
			returnJson["msg"] = err.Error()
			panic(w.WriteJson(returnJson))
			tx.Rollback()
			return
		}
		break
	case 2:		//更新系主任信息
		// 获取新的完整的系主任信息
		var oldDeanInfo,newDeanInfo  model.Tb_dean
		oldDeanInfo, err = baseGorm.QueryDeanInfo(userid)
		err = r.DecodeJsonPayload(&newDeanInfo)
		if err != nil{
			log.Fatal(err)
			returnJson["code"] = 1
			returnJson["msg"] = err.Error()
			panic(w.WriteJson(returnJson))
			return
		}
		newUserInfo := tools.StructToMapViaJson(newDeanInfo)
		updateInfo := tools.StructToMapViaJson(oldDeanInfo)
		for key, value := range newUserInfo {
			if len(value) != 0{
				updateInfo[key] = value
			}
		}

		// 可能更新密码
		err  = updatePwdInUserTable(tx, userInfo, newUserInfo["Dpassword"])
		if err != nil {
			log.Fatal(err)
			returnJson["code"] = 1
			returnJson["msg"] = err.Error()
			panic(w.WriteJson(returnJson))
			tx.Rollback()
			return
		}


		// 执行更新操作
		j, err := json.Marshal(updateInfo)
		json.Unmarshal(j, &newDeanInfo)
		err = baseGorm.UpdateDeanInfo(tx, newDeanInfo)
		if err != nil {
			log.Fatal(err)
			returnJson["code"] = 1
			returnJson["msg"] = err.Error()
			panic(w.WriteJson(returnJson))
			tx.Rollback()
			return
		}
		break
	default:
		returnJson["code"] = 1
		returnJson["msg"] = "Identity is incorrect"
		panic(w.WriteJson(returnJson))
		break
	}
	tx.Commit()	//提交全部事务

	returnJson["code"] = 0
	returnJson["msg"] = "user update success!"
	w.WriteJson(returnJson)
}

// 教师或系主任修改课堂信息
func (userController *UserController) UpdateClass(w rest.ResponseWriter, r *rest.Request){
	fmt.Println("userController.go:UpdateClassInfo()")
	var (
		newClassInfo    model.Tb_classinfo
		oldClassInfo	model.Tb_classinfo
		err         	error
		baseGorm    	*db.BaseGorm
		count			int
	)
	returnJson := make(map[string]interface{})

	err = r.DecodeJsonPayload(&newClassInfo)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}
	if newClassInfo.Cnumber == "" {
		returnJson["code"] = 1
		returnJson["msg"] = "can not update an unspecified class"
		panic(w.WriteJson(returnJson))
		return
	}

	//开启事务
	tx := baseGorm.GetDB().Begin()
	oldClassInfo, count, err = baseGorm.QueryClassInfo(newClassInfo.Cnumber)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		tx.Rollback()
		return
	}
	if count == 0 {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = "can not update a nonexistent class"
		panic(w.WriteJson(returnJson))
		tx.Rollback()
		return
	}

	if newClassInfo.Caddress == "" {
		newClassInfo.Caddress = oldClassInfo.Caddress
	}
	if newClassInfo.Csession == "" {
		newClassInfo.Csession = oldClassInfo.Csession
	}
	if newClassInfo.Ctime == "" {
		newClassInfo.Ctime = oldClassInfo.Ctime
	}
	if newClassInfo.Csum == 0 {
		newClassInfo.Csum = oldClassInfo.Csum
	}
	if newClassInfo.Cno == "" {
		newClassInfo.Cno = oldClassInfo.Cno
	}
	if newClassInfo.Tno == "" {
		newClassInfo.Tno = oldClassInfo.Tno
	}
	// 执行更新操作
	err = baseGorm.UpdateClassInfo(tx, newClassInfo)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		tx.Rollback()
		return
	}

	tx.Commit()//提交事务

	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	w.WriteJson(returnJson)
}


// 学生增加选课信息
func (userController *UserController) AddStuCourse(w rest.ResponseWriter, r *rest.Request){
	fmt.Println("webController.go:AddStuCourse()")
	var (
		err      		error
		newStuCourse	model.Tb_stucourse
		classInfo		model.Tb_classinfo
		baseGorm 		*db.BaseGorm
		count    		int
	)
	returnJson := make(map[string]interface{})
	err = r.DecodeJsonPayload(&newStuCourse)// 解析json请求
	if err != nil { // 解析出错
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}
	if newStuCourse.Sno == ""{
		returnJson["code"] = 1
		returnJson["msg"] = "the student id is empty!"
		panic(w.WriteJson(returnJson))
		return
	}
	if newStuCourse.Cnumber == ""{
		returnJson["code"] = 1
		returnJson["msg"] = "the course id is empty!"
		panic(w.WriteJson(returnJson))
		return
	}

	tx := baseGorm.GetDB().Begin()
	_, count, err = baseGorm.QueryStuCourseInfo(newStuCourse.Cnumber, newStuCourse.Sno)
	if count != 0 { // 用户名或密码不正确
		returnJson["code"] = 1
		returnJson["msg"] = "you had selected this course!"
		panic(w.WriteJson(returnJson))
		return
	}

	// 学生选课表执行插入
	err = db.CreateStuCourse(tx, newStuCourse)
	if err != nil {
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}

	// 修改教师授课表tb_classinfo字段Csum人数加一
	classInfo, count, err = baseGorm.QueryClassInfo(newStuCourse.Cnumber)
	if count == 0 { // 所选课堂记录不存在
		returnJson["code"] = 1
		returnJson["msg"] = "this class is nonexistent!"
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}
	if err != nil { // 查询出错
		returnJson["code"] = 1
		returnJson["msg"] = "query data from tb_classinfo error!"
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}
	//CsumToint, _ := strconv.Atoi(classInfo.Csum)
	//CsumToint += 1
	//classInfo.Csum = strconv.Itoa(CsumToint)
	classInfo.Csum = classInfo.Csum + 1
	err = baseGorm.UpdateClassInfo(tx, classInfo)
	if err != nil {
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}

	tx.Commit()

	returnJson["code"] = 0
	returnJson["msg"] = "select course success!"
	w.WriteJson(returnJson)
}

// 系主任增加排课信息 可删
func (userController *UserController) AddTeaCourse(w rest.ResponseWriter, r *rest.Request){
	fmt.Println("webController.go:AddTeaCourse()")
	var (
		err      		error
		newTeaCourse	model.Tb_teacourse
		baseGorm 		*db.BaseGorm
		count    		int
	)
	returnJson := make(map[string]interface{})
	err = r.DecodeJsonPayload(&newTeaCourse)// 解析json请求
	if err != nil { // 解析出错
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}
	if newTeaCourse.Tno == ""{
		returnJson["code"] = 1
		returnJson["msg"] = "the teacher id is empty!"
		panic(w.WriteJson(returnJson))
		return
	}
	if newTeaCourse.Cnumber == ""{
		returnJson["code"] = 1
		returnJson["msg"] = "the class id is empty!"
		panic(w.WriteJson(returnJson))
		return
	}
	if newTeaCourse.Cno == ""{
		returnJson["code"] = 1
		returnJson["msg"] = "the course id is empty!"
		panic(w.WriteJson(returnJson))
		return
	}

	tx := baseGorm.GetDB().Begin()
	_, count, err = baseGorm.QueryTeaCourseInfo(newTeaCourse.Cnumber, newTeaCourse.Cno, newTeaCourse.Tno)
	if count != 0 { // 记录已存在
		returnJson["code"] = 1
		returnJson["msg"] = "you had scheduled this class!"
		panic(w.WriteJson(returnJson))
		return
	}
	if err != nil { // 查询出错
		returnJson["code"] = 1
		returnJson["msg"] = "query data from tb_teacourse error!"
		panic(w.WriteJson(returnJson))
		return
	}
	// 执行插入
	err = db.CreateTeaCourse(tx, newTeaCourse)
	if err != nil {
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}
	tx.Commit()

	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	w.WriteJson(returnJson)
}

// 系主任增加课程信息
func (userController *UserController) AddCourse(w rest.ResponseWriter, r *rest.Request){
	fmt.Println("webController.go:AddCourse()")
	var (
		err      		error
		newCourseInfo	model.Tb_course
		baseGorm 		*db.BaseGorm
		count    		int
	)
	returnJson := make(map[string]interface{})
	err = r.DecodeJsonPayload(&newCourseInfo)// 解析json请求
	if err != nil { // 解析出错
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	if newCourseInfo.Cno == ""{
		count, err = baseGorm.QueryCourseSum()
		temp := strconv.Itoa(count+1)
		for i := 0; i < 6-len(temp) ; i++ {
			temp = "0" + temp
		}
		newCourseInfo.Cno = temp
	}

	tx := baseGorm.GetDB().Begin()
	_, count, err = baseGorm.QueryCourseInfo(newCourseInfo.Cno)
	if count != 0 { // 记录已存在
		returnJson["code"] = 1
		returnJson["msg"] = "the course ID has been exitent!"
		panic(w.WriteJson(returnJson))
		return
	}

	// 执行插入
	err = db.CreateCourseInfo(tx, newCourseInfo)
	if err != nil {
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}
	tx.Commit()

	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	w.WriteJson(returnJson)
}

// 系主任增加课堂信息
func (userController *UserController) AddClass(w rest.ResponseWriter, r *rest.Request){
	fmt.Println("webController.go:AddClass()")
	var (
		err      		error
		newClassInfo	model.Tb_classinfo
		baseGorm 		*db.BaseGorm
		count    		int
	)
	returnJson := make(map[string]interface{})
	err = r.DecodeJsonPayload(&newClassInfo)// 解析json请求
	if err != nil { // 解析出错
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}
	// 增加排课信息时，教师编号、课程编号不可为空，课堂编号自增一
	if newClassInfo.Tno == ""{
		returnJson["code"] = 1
		returnJson["msg"] = "the teacher id is empty!"
		panic(w.WriteJson(returnJson))
		return
	}
	if newClassInfo.Cnumber == ""{
		count, err = baseGorm.QueryClassSum()
		temp := strconv.Itoa(count+1)
		for i := 0; i < 6-len(temp) ; i++ {
			temp = "0" + temp
		}
		newClassInfo.Cnumber = temp
	}
	if newClassInfo.Cno == ""{
		returnJson["code"] = 1
		returnJson["msg"] = "the course id is empty!"
		panic(w.WriteJson(returnJson))
		return
	}

	tx := baseGorm.GetDB().Begin()
	_, count, err = baseGorm.QueryClassInfo(newClassInfo.Cnumber)
	if count != 0 { // 记录已存在
		returnJson["code"] = 1
		returnJson["msg"] = "you had scheduled this class!"
		panic(w.WriteJson(returnJson))
		return
	}

	// 执行插入
	err = db.CreateClassInfo(tx, newClassInfo)
	if err != nil {
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		tx.Rollback()
		panic(w.WriteJson(returnJson))
		return
	}
	tx.Commit()

	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	w.WriteJson(returnJson)
}


// 系主任修改课程信息
func (userController *UserController) UpdateCourse(w rest.ResponseWriter, r *rest.Request){
	fmt.Println("userController.go:UpdateClassInfo()")
	var (
		newCourseInfo	model.Tb_course
		err         	error
		baseGorm    	*db.BaseGorm
	)
	returnJson := make(map[string]interface{})

	err = r.DecodeJsonPayload(&newCourseInfo)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}
	if newCourseInfo.Cno == "" {
		returnJson["code"] = 1
		returnJson["msg"] = "can not update an unspecified course"
		panic(w.WriteJson(returnJson))
		return
	}

	//开启事务
	tx := baseGorm.GetDB().Begin()
	oldCourseInfo, _, err := baseGorm.QueryCourseInfo(newCourseInfo.Cno)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		tx.Rollback()
		return
	}

	if newCourseInfo.Ccredit == 0.0 {
		newCourseInfo.Ccredit = oldCourseInfo.Ccredit
	}
	if newCourseInfo.Cdept == "" {
		newCourseInfo.Cdept = oldCourseInfo.Cdept
	}
	if newCourseInfo.Chour == 0 {
		newCourseInfo.Chour = oldCourseInfo.Chour
	}
	if newCourseInfo.Cname== "" {
		newCourseInfo.Cname = oldCourseInfo.Cname
	}
	if newCourseInfo.Ctype== "" {
		newCourseInfo.Ctype = oldCourseInfo.Ctype
	}

	// 执行更新操作
	err = baseGorm.UpdateCourseInfo(tx, newCourseInfo)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		tx.Rollback()
		return
	}

	tx.Commit()//提交事务

	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	w.WriteJson(returnJson)
}

// 系主任修改教师信息
func (userController *UserController) UpdateTeacher(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:UpdateTeacher()")
	var (
		oldTeacherInfo model.Tb_teacher
		newTeacherInfo model.Tb_teacher
		err            error
		baseGorm       *db.BaseGorm
	)
	returnJson := make(map[string]interface{})
	err = r.DecodeJsonPayload(&newTeacherInfo)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}
	if newTeacherInfo.Tno == "" {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = "can not update a unspecified teacher"
		panic(w.WriteJson(returnJson))
		return
	}

	//开启事务
	tx := baseGorm.GetDB().Begin()
	oldTeacherInfo, err = baseGorm.QueryTeacherInfo(newTeacherInfo.Tno)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	if newTeacherInfo.Tphone == "" {
		newTeacherInfo.Tphone = oldTeacherInfo.Tphone
	}
	if newTeacherInfo.Tbirthday == "" {
		newTeacherInfo.Tbirthday = oldTeacherInfo.Tbirthday
	}
	if newTeacherInfo.Tpassword == "" {
		newTeacherInfo.Tpassword = oldTeacherInfo.Tpassword
	}
	if newTeacherInfo.Tsex == "" {
		newTeacherInfo.Tsex = oldTeacherInfo.Tsex
	}
	if newTeacherInfo.Tname == "" {
		newTeacherInfo.Tname = oldTeacherInfo.Tname
	}
	if newTeacherInfo.Tdept == ""{
		newTeacherInfo.Tdept = oldTeacherInfo.Tdept
	}

	// 执行更新操作
	err = baseGorm.UpdateTeacherInfo(tx, newTeacherInfo)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		tx.Rollback()
		return
	}

	tx.Commit()	//提交全部事务

	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	w.WriteJson(returnJson)
}

// 系主任修改学生信息
func (userController *UserController) UpdateStudent(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:UpdateStudent()")
	var (
		oldStudentInfo model.Tb_student
		newStudentInfo model.Tb_student
		err            error
		baseGorm       *db.BaseGorm
	)
	returnJson := make(map[string]interface{})
	err = r.DecodeJsonPayload(&newStudentInfo)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}
	if newStudentInfo.Sno == "" {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = "can not update a unspecified student"
		panic(w.WriteJson(returnJson))
		return
	}

	//开启事务
	tx := baseGorm.GetDB().Begin()
	oldStudentInfo, err = baseGorm.QueryStudentInfo(newStudentInfo.Sno)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		return
	}

	if newStudentInfo.Smajor == "" {
		newStudentInfo.Smajor = oldStudentInfo.Smajor
	}
	if newStudentInfo.Sclass == "" {
		newStudentInfo.Sclass = oldStudentInfo.Sclass
	}
	if newStudentInfo.Sbirthday == "" {
		newStudentInfo.Sbirthday = oldStudentInfo.Sbirthday
	}
	if newStudentInfo.Spassword == "" {
		newStudentInfo.Spassword = oldStudentInfo.Spassword
	}
	if newStudentInfo.Sname == "" {
		newStudentInfo.Sname = oldStudentInfo.Sname
	}
	if newStudentInfo.Ssex == ""{
		newStudentInfo.Ssex = oldStudentInfo.Ssex
	}

	// 执行更新操作
	err = baseGorm.UpdateStudentInfo(tx, newStudentInfo)
	if err != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		tx.Rollback()
		return
	}

	tx.Commit()	//提交全部事务

	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	w.WriteJson(returnJson)
}

// 系主任删除课程信息
func (userController *UserController) DeleteCourse(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:DeleteCourse()")
	//returnJson := make(map[string]interface{})

	id := r.PathParam("Cno")
	doDelete(w, id, 0)
	//开启事务
	//baseGorm:=db.BaseGorm{}
	//tx := baseGorm.GetDB().Begin()
	//err := db.DeleteCourse(tx, id)
	//if err != nil {
	//	log.Fatal(err)
	//	returnJson["code"] = 1
	//	returnJson["msg"] = err.Error()
	//	panic(w.WriteJson(returnJson))
	//	tx.Rollback()
	//	return
	//}
	//tx.Commit()
	//
	//returnJson["code"] = 0
	//returnJson["msg"] = "delete user success!"
	//w.WriteJson(returnJson)
}

// 系主任删除课堂信息
func (userController *UserController) DeleteClass(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:DeleteClass()")
	//returnJson := make(map[string]interface{})

	id := r.PathParam("Cnumber")
	doDelete(w, id, 1)
}

// 系主任删除教师信息
func (userController *UserController) DeleteTeacher(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:DeleteTeacher()")
	id := r.PathParam("Tno")
	doDelete(w, id, 2)
}

// 系主任删除学生信息
func (userController *UserController) DeleteStudent(w rest.ResponseWriter, r *rest.Request) {
	fmt.Println("userController.go:DeleteStudent()")
	id := r.PathParam("Sno")
	doDelete(w, id, 3)
}

// 执行删除事务
func doDelete(w rest.ResponseWriter, id string, sel int)  {
	//开启事务
	returnJson := make(map[string]interface{})
	var err error
	var err1 error
	baseGorm:=db.BaseGorm{}
	tx := baseGorm.GetDB().Begin()
	switch sel {
	case 0:
		err = db.DeleteCourse(tx, id)
		break
	case 1:
		err = db.DeleteClassInfo(tx, id)
		break
	case 2:
		err = db.DeleteTeacher(tx, id)
		err1 = db.DeleteUser(tx, id)
		break
	case 3:
		err = db.DeleteStudent(tx, id)
		err1 = db.DeleteUser(tx, id)
		break
	default:
		return
	}

	if err != nil || err1 != nil {
		log.Fatal(err)
		returnJson["code"] = 1
		returnJson["msg"] = err.Error()
		panic(w.WriteJson(returnJson))
		tx.Rollback()
		return
	}
	tx.Commit()

	returnJson["code"] = 0
	returnJson["msg"] = "success!"
	w.WriteJson(returnJson)
}
