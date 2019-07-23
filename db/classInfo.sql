CREATE TABLE tb_classInfo(
	Cnumber char(6) NOT NULL COMMENT '课堂编号',
    Ctime date not null comment '上课日期',
    Csession varchar(20) not null comment '课堂节次',
    Caddress varchar(20) not null comment '上课地点',
	FOREIGN KEY (Cnumber) REFERENCES tb_teacourse(Cnumber)
)