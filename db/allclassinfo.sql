-- 所有课堂信息视图
create view allclassinfo as select tb_classinfo.Cnumber,
tb_classinfo.Ctime, tb_classinfo.Csession, tb_classinfo.Caddress, tb_classinfo.Csum,
tb_course.Cno, tb_course.Cname, tb_teacher.Tno, tb_teacher.Tname
from tb_course,tb_classinfo,tb_teacher
where tb_course.Cno = tb_classinfo.Cno AND tb_teacher.Tno = tb_classinfo.Tno;