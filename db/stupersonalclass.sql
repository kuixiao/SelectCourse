--课堂编号课 程名称  学分 学时 时间 节次 地点 教师姓名 学号
create view stupersonalclass as select tb_classinfo.Cnumber,  
tb_course.Cname , tb_course.Ccredit , tb_course.Chour,
tb_classinfo.Ctime, tb_classinfo.Csession, tb_classinfo.Caddress,
tb_teacher.Tname, tb_stucourse.Sno
from tb_course,tb_classinfo,tb_teacher,tb_stucourse
where tb_stucourse.Cnumber = tb_classinfo.Cnumber  
AND tb_course.Cno = tb_classinfo.Cno
AND tb_classinfo.Tno = tb_teacher.Tno ;