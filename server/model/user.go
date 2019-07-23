package model

// 用户登录表
type Tb_user struct {
	Id          string  `gorm:"column:id;primary_key;AUTO_INCREMENT"`	//账号
	Pwd     	string	`gorm:"column:pwd"`								//密码
	Identity    int		`gorm:"column:identity"`						//身份 0系主任 1教师 2学生
	Token		string	`gorm:"column:token"`							//通信令牌
	Deadline	string	`gorm:"column:deadline"`						//登录时间
}

// 课堂信息结构体
type Tb_classinfo struct {
	Cnumber		string	`gorm:"column:Cnumber"`	//课堂编号
	Ctime	    string	`gorm:"column:Ctime"`	//上课日期
	Csession    string	`gorm:"column:Csession"`//课堂节次
	Caddress    string	`gorm:"column:Caddress"`//上课地点
	Csum		int		`gorm:"column:Csum"`	//课堂人数
	Cno			string	`gorm:"column:Cno"`		//课程编号
	Tno			string	`gorm:"column:Tno"`		//教师编号
}

// 课程信息结构体
type Tb_course struct {
	Cno			string 	`gorm:"column:Cno"`		//课程代码
	Cname     	string 	`gorm:"column:Cname"`	//课程名称
	Ccredit     float32 `gorm:"column:Ccredit"`	//学分
	Chour      	int 	`gorm:"column:Chour"`	//学时
	Ctype       string 	`gorm:"column:Ctype"`	//课程类型
	Cdept       string 	`gorm:"column:Cdept"`	//开课院系
}

// 学生选课表
type Tb_stucourse struct {
	Cnumber		string `gorm:"column:Cnumber"`	//课堂编号
	Sno     	string `gorm:"column:Sno"`		//学生学号
}

// 学生信息表
type Tb_student struct {
	Sno			string `gorm:"column:Sno"`		//学号
	Smajor     	string `gorm:"column:Smajor"`	//专业
	Sname     	string `gorm:"column:Sname"`	//名字
	Ssex		string `gorm:"column:Ssex"`		//性别
	Sbirthday	string `gorm:"column:Sbirthday"`//出生日期
	//Sphone		string `gorm:"column:Sphone"`	//电话
	Sclass		string `gorm:"column:Sclass"`	//班级
	Spassword	string `gorm:"column:Spassword"`//密码
}

// 教师信息表
type Tb_teacher struct {
	Tno			string `gorm:"column:Tno;primary_key"`	//教师职工编号
	Tname     	string `gorm:"column:Tname"`			//教师姓名
	Tsex     	string `gorm:"column:Tsex"`				//教师性别
	Tbirthday	string `gorm:"column:Tbirthday"`		//教师出生日期
	Tdept       string `gorm:"column:Tdept"`			//教师所属院系
	Tphone     	string `gorm:"column:Tphone"`			//教师联系电话
	Tpassword 	string `gorm:"column:Tpassword"`		//教师登录密码
}

// 教师授课表 可删
type Tb_teacourse struct {
	Cnumber	string	`gorm:"column:Cnumber"`	//课堂编号
	Tno     string 	`gorm:"column:Tno"`		//教师职工编号
	Cno     string	`gorm:"column:Cno"`		//课程代码
}

// 系主任信息表
type Tb_dean struct {
	Dno			string `gorm:"column:Dno;primary_key"`	//系主任职工编号
	Dname     	string `gorm:"column:Dname"`			//系主任姓名
	Dsex     	string `gorm:"column:Dsex"`				//系主任性别
	Dbirthday	string `gorm:"column:Dbirthday"`		//系主任出生日期
	Ddept       string `gorm:"column:Ddept"`			//系主任所属院系
	Dphone     	string `gorm:"column:Dphone"`			//系主任联系电话
	Dpassword 	string `gorm:"column:Dpassword"`		//系主任登录密码
}

// 某一课堂所有学生信息视图
type Studentofclass struct {
	Cnumber		string `gorm:"column:Cnumber"`	//课堂编号
	Sno			string `gorm:"column:Sno"`		//学号
	Smajor     	string `gorm:"column:Smajor"`	//专业
	Sname     	string `gorm:"column:Sname"`	//名字
	Ssex		string `gorm:"column:Ssex"`		//性别
	//Sphone		string `gorm:"column:Sphone"`	//电话
	Sclass		string `gorm:"column:Sclass"`	//班级
}

// 学生选课课堂信息信息视图
type Stuclass struct {
	Cno			string	`gorm:"column:Cno"`		//课程编号
	Cname     	string 	`gorm:"column:Cname"`	//课程名称
	Ccredit     float32 `gorm:"column:Ccredit"`	//学分
	Chour      	int 	`gorm:"column:Chour"`	//学时

	Cnumber		string	`gorm:"column:Cnumber"`	//课堂编号
	Ctime	    string	`gorm:"column:Ctime"`	//上课日期
	Csession    string	`gorm:"column:Csession"`//课堂节次
	Caddress    string	`gorm:"column:Caddress"`//上课地点

	Tno			string	`gorm:"column:Tno"`		//教师编号
	Tname     	string  `gorm:"column:Tname"`	//教师姓名
}

// 教师个人课堂信息视图
type Personalclass struct {
	Tno			string	`gorm:"column:Tno"`		//教师职工编号
	Cnumber		string	`gorm:"column:Cnumber"`	//课堂编号
	Cno			string 	`gorm:"column:Cno"`		//课程代码
	Cname     	string 	`gorm:"column:Cname"`	//课程名称
	Ccredit     float32 `gorm:"column:Ccredit"`	//学分
	Chour      	int 	`gorm:"column:Chour"`	//学时
	Ctype       string 	`gorm:"column:Ctype"`	//课程类型
	Cdept       string 	`gorm:"column:Cdept"`	//开课院系
	Ctime	    string	`gorm:"column:Ctime"`	//上课日期
	Csession    string	`gorm:"column:Csession"`//课堂节次
	Caddress    string	`gorm:"column:Caddress"`//上课地点
	Csum		int		`gorm:"column:Csum"`	//课堂人数
}

// 学生个人选课结果信息视图
type Stupersonalclass struct {
	Cnumber		string	`gorm:"column:Cnumber"`	//课堂编号
	Cname     	string 	`gorm:"column:Cname"`	//课程名称
	Ccredit     float32 `gorm:"column:Ccredit"`	//学分
	Chour      	int 	`gorm:"column:Chour"`	//学时
	Ctime	    string	`gorm:"column:Ctime"`	//上课日期
	Csession    string	`gorm:"column:Csession"`//课堂节次
	Caddress    string	`gorm:"column:Caddress"`//上课地点
	Tname     	string  `gorm:"column:Tname"`	//教师姓名
	Sno			string	`gorm:"column:Sno"`		//学号
}

// 系主任查看所有课堂信息视图
type Allclassinfo struct {
	Cnumber		string	`gorm:"column:Cnumber"`	//课堂编号
	Ctime	    string	`gorm:"column:Ctime"`	//上课日期
	Csession    string	`gorm:"column:Csession"`//课堂节次
	Caddress    string	`gorm:"column:Caddress"`//上课地点
	Csum		int		`gorm:"column:Csum"`	//课堂人数
	Cno			string	`gorm:"column:Cno"`		//课程编号
	Cname     	string 	`gorm:"column:Cname"`	//课程名称
	Tno			string	`gorm:"column:Tno"`		//教师编号
	Tname     	string  `gorm:"column:Tname"`	//教师姓名
}









type User_info struct {
	Id          int    `gorm:"column:Id;primary_key;AUTO_INCREMENT"`
	UserName    string `gorm:"column:userName"`
	Nickname    string `gorm:"column:nickname"`
	Tel         string `gorm:"column:tel"`
	Email       string `gorm:"column:email"`
	Token       string `gorm:"column:token"`
	Deadline	string `gorm:"column:deadline"`
	Pwd     	string `gorm:"column:pwd"`
}