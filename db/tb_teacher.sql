CREATE TABLE tb_teacher(
	Tno char(6) NOT NULL PRIMARY KEY comment '教师职工编号',
	Tname varchar(20) NOT NULL comment '教师姓名',
	Tsex char(2) NOT NULL comment '教师性别' check(Tsex = '男' or Tsex = '女'),
	Tbirthday datetime NOT NULL comment '教师出生日期',
	Tdept varchar(20) NOT NULL comment '教师所属院系',
    Tphone varchar(11) NOT NULL comment '教师联系电话',
    Tpassword varchar(20) NOT NULL COMMENT '教师登录密码'
    )
    