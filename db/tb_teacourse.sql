CREATE TABLE tb_teacourse(
	Cnumber varchar(6) PRIMARY KEY NOT NULL COMMENT '课堂编号',
	Tno char(6) NOT NULL comment '教师职工编号',
    Cno VARCHAR(6) NOT NULL comment '课程代码',
	FOREIGN KEY (Cno) REFERENCES tb_course(Cno),
	FOREIGN KEY (Tno) REFERENCES tb_teacher(Tno)
)