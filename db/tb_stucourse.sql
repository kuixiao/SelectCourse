CREATE TABLE tb_stucourse(
	Cnumber char(6) NOT NULL COMMENT '课堂编号',
    Sno CHAR(6) NOT NULL comment '学生学号',
    primary key (Sno, Cnumber),
	FOREIGN KEY (Cnumber) REFERENCES tb_teacourse(Cnumber),
	FOREIGN KEY (Sno) REFERENCES tb_student(Sno)
)