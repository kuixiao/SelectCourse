CREATE TABLE tb_deantb_dean(
	Dno char(6) NOT NULL PRIMARY KEY comment '系主任职工编号',
	Dname varchar(20) NOT NULL comment '系主任姓名',
	Dsex char(2) NOT NULL comment '系主任性别' check(Tsex = '男' or Tsex = '女'),
	Dbirthday datetime NOT NULL comment '系主任出生日期',
	Ddept varchar(20) NOT NULL comment '系主任所属院系',
    Dphone varchar(11) NOT NULL comment '系主任联系电话',
    Dpassword varchar(20) NOT NULL COMMENT '系主任登录密码'
    )
    