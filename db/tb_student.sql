CREATE TABLE tb_student(
	Sno char(6) NOT NULL PRIMARY KEY comment '学号',
	Smajor char(20) NOT NULL comment '专业',
	Sname varchar(20) NULL comment '名字',
	Ssex char(2) NOT NULL comment '性别' check(Ssex = '男' or Ssex = '女'),
	Sbirthday date NOT NULL comment '出生日期',
	Spassword varchar(20) NOT NULL comment '密码',
	Sclass varchar(20) not null comment '班级'
)