CREATE TABLE tb_course (
    Cno char(6) NOT NULL PRIMARY KEY comment '课程代码',
    Cname VARCHAR(20) NOT NULL COMMENT '课程名称',
    Ccredit FLOAT NOT NULL COMMENT '学分',
    Chour SMALLINT NOT NULL COMMENT '学时',
    Ctype VARCHAR(20) NOT NULL COMMENT '课程类型',
    Cdept VARCHAR(20) NOT NULL comment '开课院系'
)