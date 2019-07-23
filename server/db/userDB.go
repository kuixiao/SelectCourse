package db

import (
	"../model"
	"fmt"
	"github.com/jinzhu/gorm"
)


// 根据用户id查询用户表
func (baseGorm *BaseGorm)QueryUserInfo(id string) (userInfo model.Tb_user,count int,err error){
	if id == ""{
		if err = baseGorm.GetDB().Table("tb_user").Find(&userInfo).Count(&count).Error; err != nil {
			return  userInfo, count,err
		}
	}
	if id != "" {
		if err = baseGorm.GetDB().Table("tb_user").Where("id = ?", id).Find(&userInfo).Count(&count).Error; err != nil {
			return  userInfo, count,err
		}
	}
	return userInfo, count, err
}

// 登录时从用户表查询用户并返回用户信息
func (baseGorm *BaseGorm)QueryUserInForLogin(userNo string, password string) (userInfo model.Tb_user, count int, err error){
	fmt.Println("userDB.go:QueryUserInForLogin()")
	if err = baseGorm.GetDB().Table("tb_user").Where("id = ? AND pwd = ?", userNo, password).Find(&userInfo).Count(&count).Error; err != nil {
		return userInfo, count, err
	}
	return userInfo, count, err
}

// 根据令牌查询用户登录表并返回查询结果
func (baseGorm *BaseGorm) QueryUseInfoByToken(token string) (userInfo model.Tb_user,count int, err error) {
	fmt.Println("userDB.go：QueryUseInfoByToken()")
	if err = baseGorm.GetDB().Where("token = ?", token).Find(&userInfo).Count(&count).Error; err != nil {
		return userInfo,count, err
	}
	return userInfo,count, err
}



// 用户登录表创建新用户
func CreateUser(db *gorm.DB, userInfo model.Tb_user)  (err error){
	fmt.Println("CreateUser")
	if err = db.Create(&userInfo).Error; err != nil {
		return err
	}
	return nil
}

// 教师表创建新教师用户
func CreateTeacher(db *gorm.DB, teacherInfo model.Tb_teacher) (err error) {
	fmt.Println("CreateTeacher")
	if err = db.Create(&teacherInfo).Error; err != nil {
		return err
	}
	user := model.Tb_user{
		Id:			teacherInfo.Tno,
		Pwd:		teacherInfo.Tpassword,
		Identity:	1,
	}
	CreateUser(db, user)
	return nil
}

// 学生表创建学生用户
func CreateStudent(db *gorm.DB, studentInfo model.Tb_student) (err error) {
	fmt.Println("CreateTeacher")
	if err = db.Create(&studentInfo).Error; err != nil {
		return err
	}
	userInfo := model.Tb_user{
		Id:			studentInfo.Sno,
		Pwd:		studentInfo.Spassword,
		Identity:	0,
	}
	CreateUser(db, userInfo)
	return nil
}

// 排课表创建新排课记录
func CreateTeaCourse(db *gorm.DB, teaCourseInfo model.Tb_teacourse) (err error) {
	fmt.Println("userDB.go:CreateTeaCourse()")
	if err = db.Create(&teaCourseInfo).Error; err != nil {
		return err
	}
	return nil
}

// 课程表创建新课堂记录
func CreateCourseInfo(db *gorm.DB, courseInfo model.Tb_course) (err error) {
	fmt.Println("userDB.go:CreateCourseInfo()")
	if err = db.Create(&courseInfo).Error; err != nil {
		return err
	}
	return nil
}

// 课堂表创建新排课记录
func CreateClassInfo(db *gorm.DB, classInfo model.Tb_classinfo) (err error) {
	fmt.Println("userDB.go:CreateTeaCourse()")
	if err = db.Create(&classInfo).Error; err != nil {
		return err
	}
	return nil
}

// 选课表创建新选课记录
func CreateStuCourse(db *gorm.DB, stuCourseInfo model.Tb_stucourse) (err error) {
	fmt.Println("userDB.go:CreateStuCourse()")
	if err = db.Create(&stuCourseInfo).Error; err != nil {
		return err
	}
	return nil
}





// 查询某一学生信息
func (baseGorm *BaseGorm) QueryStudentInfo(studentId string) (studentInfo model.Tb_student, err error) {
	fmt.Println("userDB.go：QueryStudentInfo()")
	if err = baseGorm.GetDB().Where("Sno = ?", studentId).Find(&studentInfo).Error; err != nil {
		return studentInfo, err
	}
	return studentInfo, nil
}

// 查询某位教师信息
func (baseGorm *BaseGorm) QueryTeacherInfo(teacherId string) (teacherInfo model.Tb_teacher, err error) {
	fmt.Println("userDB.go：QueryTeacherInfo()")
	if err = baseGorm.GetDB().Where("Tno = ?", teacherId).Find(&teacherInfo).Error; err != nil {
		return teacherInfo, err
	}
	return teacherInfo, nil
}

// 查询某位系主任信息
func (baseGorm *BaseGorm) QueryDeanInfo(deanId string) (deanInfo model.Tb_dean, err error){
	fmt.Println("userDB.go：QueryDeanInfo()")
	if err = baseGorm.GetDB().Where("Dno = ?", deanId).Find(&deanInfo).Error; err != nil {
		return deanInfo, err
	}
	return deanInfo, nil
}

// 查询所有学生信息
func (baseGorm *BaseGorm) QueryAllStudentInfo() (allStudentInfo []model.Tb_student, err error) {
	fmt.Println("userDB.go:QueryAllStudentInfo")
	if err := baseGorm.GetDB().Model(&model.Tb_student{}).Find(&allStudentInfo ).Error; err != nil {
		return allStudentInfo , err
	}
	return allStudentInfo , nil
}

// 查询某位教师所有课堂信息
func (baseGorm *BaseGorm) QueryTeaPersonalClassInfo (Tno string) (personalClassInfo []model.Personalclass, err error) {
	fmt.Println("userDB.go:QueryPersonalClassInfo()")
	if err := baseGorm.GetDB().Model(&model.Personalclass{}).Where("Tno = ?", Tno).Find(&personalClassInfo).Error; err != nil {
		return personalClassInfo , err
	}
	return personalClassInfo , nil
}

// 查询某位学生选课结果信息
func (baseGorm *BaseGorm) QueryStuPersonalClassInfo (Sno string) (personalClassInfo []model.Stupersonalclass, err error) {
	fmt.Println("userDB.go:QueryStuPersonalClassInfo()")
	if err := baseGorm.GetDB().Model(&model.Stupersonalclass{}).Where("Sno = ?", Sno).Find(&personalClassInfo).Error; err != nil {
		return personalClassInfo , err
	}
	return personalClassInfo , nil
}

// 查询某一课堂所有学生信息
func (baseGorm *BaseGorm) QueryAllStudentInfoOfClass(Cnumber string) (allStudentInfo []model.Studentofclass, err error) {
	fmt.Println("userDB.go:QueryAllStudentInfoOfClass")
	if err := baseGorm.GetDB().Model(&model.Studentofclass{}).Where("Cnumber = ?", Cnumber).Find(&allStudentInfo ).Error; err != nil {
		return allStudentInfo , err
	}
	return allStudentInfo , nil
}

// 查询所有教师信息
func (baseGorm *BaseGorm) QueryAllTeacherInfo() (allTeacherInfo []model.Tb_teacher, err error) {
	fmt.Println("userDB.go:QueryAllTeacherInfo()")
	if err := baseGorm.GetDB().Model(&model.Tb_teacher{}).Find(&allTeacherInfo ).Error; err != nil {
		return allTeacherInfo , err
	}
	return allTeacherInfo , nil
}

// 查询所有课程信息
func (baseGorm *BaseGorm) QueryAllCourseInfo() (allCourseInfo []model.Tb_course, err error) {
	fmt.Println("userDB.go:QueryAllCourseInfo()")
	if err := baseGorm.GetDB().Model(&model.Tb_course{}).Find(&allCourseInfo ).Error; err != nil {
		return allCourseInfo , err
	}
	return allCourseInfo , nil
}

// 查询所有课程信息
func (baseGorm *BaseGorm) QueryAllClassInfo() (allclassinfo []model.Allclassinfo, err error) {
	fmt.Println("userDB.go:QueryAllCourseInfo()")
	if err := baseGorm.GetDB().Model(&model.Allclassinfo{}).Find(&allclassinfo ).Error; err != nil {
		return allclassinfo , err
	}
	return allclassinfo , nil
}

// 查询所有选课课堂信息
func (baseGorm *BaseGorm) QueryStuClassInfo() (stuClassInfo []model.Stuclass, err error) {
	fmt.Println("userDB.go:QueryStuClassInfo()")
	if err := baseGorm.GetDB().Model(&model.Stuclass{}).Find(&stuClassInfo).Error; err != nil {
		return stuClassInfo, err
	}
	return stuClassInfo, nil
}

// 查询某一课程信息
func (baseGorm *BaseGorm) QueryCourseInfo(courseId string) (courseInfo model.Tb_course, count int, err error) {
	fmt.Println("userDB.go：QueryCourseInfo()")
	if err = baseGorm.GetDB().Where("Cno = ?", courseId).Find(&courseInfo).Count(&count).Error; err != nil {
		return courseInfo, count, err
	}
	return courseInfo, count,nil
}

// 查询某一课堂信息
func (baseGorm *BaseGorm) QueryClassInfo(Cnumber string) (classInfo model.Tb_classinfo,count int, err error) {
	fmt.Println("userDB.go：QueryClassInfo()")
	if err = baseGorm.GetDB().Where("Cnumber = ?", Cnumber).Find(&classInfo).Count(&count).Error; err != nil {
		return classInfo, count, err
	}
	return classInfo, count, nil
}

// 查询课程数量
func (baseGorm *BaseGorm) QueryCourseSum() (count int, err error) {
	fmt.Println("userDB.go：QueryCourseSum()")
	if err = baseGorm.GetDB().Model(model.Tb_course{}).Count(&count).Error; err != nil {
		return count, err
	}
	return count, nil
}

// 查询课堂数量
func (baseGorm *BaseGorm) QueryClassSum() (count int, err error) {
	fmt.Println("userDB.go：QueryClassInfo()")
	if err = baseGorm.GetDB().Model(model.Tb_classinfo{}).Count(&count).Error; err != nil {
		return count, err
	}
	return count, nil
}

// 查询某一排课信息
func (baseGorm *BaseGorm) QueryTeaCourseInfo(Cnumber string, Cno string, Tno string) (teaCourseInfo model.Tb_teacourse, count int, err error) {
	fmt.Println("userDB.go：QueryTeaCourseInfo()")
	if err = baseGorm.GetDB().Where("Cnumber = ? AND Cno = ? AND Tno = ?", Cnumber, Cno, Tno).Find(&teaCourseInfo).Count(&count).Error; err != nil {
		return teaCourseInfo,count, err
	}
	return teaCourseInfo,count, err
}

// 查询选课信息表
func (baseGorm *BaseGorm) QueryStuCourseInfo(Cnumber string, Sno string) (stuCourseInfo model.Tb_stucourse, count int, err error) {
	fmt.Println("userDB.go：QueryStuCourseInfo()")
	if err = baseGorm.GetDB().Where("Cnumber = ? AND Sno = ?", Cnumber, Sno).Find(&stuCourseInfo).Count(&count).Error; err != nil {
		return stuCourseInfo,count, err
	}
	return stuCourseInfo,count, err
}





// 更新用户登录表信息
func (baseGorm *BaseGorm)UpdateUserTable(db *gorm.DB,  userInfo model.Tb_user) (err error) {
	fmt.Println("userDB.go:UpdateUserTable()")
	//if err = db.Model(model.Tb_user{}).Where("id = ?", userInfo.Id).Updates(map[string]interface{}{"Token":userInfo.Token,"Deadline":userInfo.Deadline,"Pwd":userInfo.Pwd}).Error; err != nil {
	if err = db.Model(model.Tb_user{}).Where("id = ?", userInfo.Id).Updates(&userInfo).Error; err != nil {
		return err
	}
	return nil
}

// 更新学生信息
func (baseGorm *BaseGorm)UpdateStudentInfo(db *gorm.DB, studentInfo model.Tb_student) (err error) {
	fmt.Println("userDB.go:UpdateStudentInfo()")
	if err = db.Model(model.Tb_student{}).Where("Sno = ?", studentInfo.Sno).Update(&studentInfo).Error; err != nil {
		return err
	}
	return nil
}

// 更新教师信息
func (baseGorm *BaseGorm)UpdateTeacherInfo(db *gorm.DB, teacherInfo model.Tb_teacher) (err error) {
	fmt.Println("userDB.go:UpdateStudentInfo()")
	if err = db.Model(model.Tb_teacher{}).Where("Tno = ?", teacherInfo.Tno).Update(teacherInfo).Error; err != nil {
		return err
	}
	return nil
}

// 更新系主任信息
func (baseGorm *BaseGorm)UpdateDeanInfo(db *gorm.DB, deanInfo model.Tb_dean) (err error) {
	fmt.Println("userDB.go:UpdateDeanInfo()")
	if err = db.Model(model.Tb_dean{}).Where("Dno = ?", deanInfo.Dno).Updates(&deanInfo).Error; err != nil{
		return err
	}
	return nil

}

// 更新课程信息
func (baseGorm *BaseGorm)UpdateCourseInfo(db *gorm.DB, courseInfo model.Tb_course) (err error) {
	fmt.Println("userDB.go:UpdateStudentInfo()")
	if err = db.Model(model.Tb_course{}).Where("Cno = ?", courseInfo.Cno).Update(&courseInfo).Error; err != nil {
		return err
	}
	return nil
}

// 更新课堂信息
func (baseGorm *BaseGorm)UpdateClassInfo(db *gorm.DB, classInfo model.Tb_classinfo) (err error) {
	fmt.Println("userDB.go:UpdateStudentInfo()")
	if err = db.Model(model.Tb_classinfo{}).Where("Cnumber = ?", classInfo.Cnumber).Update(&classInfo).Error; err != nil {
		return err
	}
	return nil
}


// 用户表删除用户信息
func DeleteUser(db *gorm.DB, userID string) (err error) {
	fmt.Println("userDB.go:DeleteUser()")
	if err = db.Where("ID = ?", userID).Delete(model.Tb_user{}).Error; err != nil {
		return err
	}
	return nil
}

// 删除课程信息
func DeleteCourse(db *gorm.DB, Cno string) (err error) {
	fmt.Println("userDB.go:DeleteCourse()")
	if err = db.Where("Cno = ?", Cno).Delete(model.Tb_course{}).Error; err != nil {
		return err
	}
	return nil
}

// 删除课堂信息
func DeleteClassInfo(db *gorm.DB, Cnumber string) (err error) {
	fmt.Println("userDB.go:DeleteClassInfo()")
	if err = db.Where("Cnumber = ?", Cnumber).Delete(model.Tb_classinfo{}).Error; err != nil {
		return err
	}
	return nil
}

// 删除教师信息
func DeleteTeacher(db *gorm.DB, Tno string) (err error) {
	fmt.Println("userDB.go:DeleteTeacher()")
	if err = db.Where("Tno = ?", Tno).Delete(model.Tb_student{}).Error; err != nil {
		return err
	}
	return nil
}

//删除学生信息
func DeleteStudent(db *gorm.DB, Sno string) (err error) {
	fmt.Println("userDB.go:DeleteStudent()")
	if err = db.Where("Sno = ?", Sno).Delete(model.Tb_student{}).Error; err != nil {
		return err
	}
	return nil
}

