
--课堂编号 课程代码 课程名称  学分 学时 时间 节次 地点 人数 教师职工编号 教师姓名
create view stuclass as select tb_classinfo.Cnumber, tb_classinfo.Cno,  
tb_course.Cname , tb_course.Ccredit , tb_course.Chour,
tb_classinfo.Ctime, tb_classinfo.Csession, tb_classinfo.Caddress,
tb_teacher.Tno, tb_teacher.Tname 
from tb_course,tb_classinfo,tb_teacher
where tb_course.Cno = tb_classinfo.Cno AND tb_classinfo.Tno = tb_teacher.Tno;