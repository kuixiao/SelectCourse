CREATE TABLE tb_user(
	id int NOT NULL primary key auto_increment COMMENT '账号',
    pwd varchar(20) not null comment '密码',
    identity int comment '身份' check( identity > 0 and identify < 10)
);
