-- MySQL dump 10.13  Distrib 5.7.26, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: SelectCourse
-- ------------------------------------------------------
-- Server version	5.7.26-0ubuntu0.18.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Temporary table structure for view `allclassinfo`
--

DROP TABLE IF EXISTS `allclassinfo`;
/*!50001 DROP VIEW IF EXISTS `allclassinfo`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `allclassinfo` AS SELECT 
 1 AS `Cnumber`,
 1 AS `Ctime`,
 1 AS `Csession`,
 1 AS `Caddress`,
 1 AS `Csum`,
 1 AS `Cno`,
 1 AS `Cname`,
 1 AS `Tno`,
 1 AS `Tname`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `personalclass`
--

DROP TABLE IF EXISTS `personalclass`;
/*!50001 DROP VIEW IF EXISTS `personalclass`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `personalclass` AS SELECT 
 1 AS `Tno`,
 1 AS `Cnumber`,
 1 AS `Cno`,
 1 AS `Cname`,
 1 AS `Ccredit`,
 1 AS `Chour`,
 1 AS `Ctype`,
 1 AS `Cdept`,
 1 AS `Ctime`,
 1 AS `Csession`,
 1 AS `Caddress`,
 1 AS `Csum`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `stuclass`
--

DROP TABLE IF EXISTS `stuclass`;
/*!50001 DROP VIEW IF EXISTS `stuclass`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `stuclass` AS SELECT 
 1 AS `Cnumber`,
 1 AS `Cno`,
 1 AS `Cname`,
 1 AS `Ccredit`,
 1 AS `Chour`,
 1 AS `Ctime`,
 1 AS `Csession`,
 1 AS `Caddress`,
 1 AS `Tno`,
 1 AS `Tname`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `studentofclass`
--

DROP TABLE IF EXISTS `studentofclass`;
/*!50001 DROP VIEW IF EXISTS `studentofclass`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `studentofclass` AS SELECT 
 1 AS `Cnumber`,
 1 AS `Sno`,
 1 AS `Sname`,
 1 AS `Sclass`,
 1 AS `Smajor`,
 1 AS `Ssex`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `stupersonalclass`
--

DROP TABLE IF EXISTS `stupersonalclass`;
/*!50001 DROP VIEW IF EXISTS `stupersonalclass`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `stupersonalclass` AS SELECT 
 1 AS `Cnumber`,
 1 AS `Cname`,
 1 AS `Ccredit`,
 1 AS `Chour`,
 1 AS `Ctime`,
 1 AS `Csession`,
 1 AS `Caddress`,
 1 AS `Tname`,
 1 AS `Sno`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `tb_classinfo`
--

DROP TABLE IF EXISTS `tb_classinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_classinfo` (
  `Cnumber` char(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '课堂编号',
  `Ctime` date DEFAULT NULL COMMENT '上课日期',
  `Csession` varchar(20) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '课堂节次',
  `Caddress` varchar(20) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '上课地点',
  `Csum` int(11) DEFAULT NULL COMMENT '选课人数',
  `Cno` char(6) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '课程代码',
  `Tno` char(6) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '教师职工编号',
  PRIMARY KEY (`Cnumber`),
  KEY `Tno` (`Tno`),
  KEY `Cno` (`Cno`),
  CONSTRAINT `tb_classinfo_ibfk_1` FOREIGN KEY (`Tno`) REFERENCES `tb_teacher` (`Tno`),
  CONSTRAINT `tb_classinfo_ibfk_2` FOREIGN KEY (`Cno`) REFERENCES `tb_course` (`Cno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_classinfo`
--

LOCK TABLES `tb_classinfo` WRITE;
/*!40000 ALTER TABLE `tb_classinfo` DISABLE KEYS */;
INSERT INTO `tb_classinfo` VALUES ('000002','2019-03-14','3-4','西十二N01',33,'000004','T00002'),('000003','2019-04-05','7-8','东五楼129',34,'000001','T00003'),('0001','2019-03-03','5-6','西十二S302',90,'000003','T00001');
/*!40000 ALTER TABLE `tb_classinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_course`
--

DROP TABLE IF EXISTS `tb_course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_course` (
  `Cno` char(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '课程代码',
  `Cname` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '课程名称',
  `Ccredit` float NOT NULL COMMENT '学分',
  `Chour` smallint(6) NOT NULL COMMENT '学时',
  `Ctype` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '课程类型',
  `Cdept` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '开课院系',
  PRIMARY KEY (`Cno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_course`
--

LOCK TABLES `tb_course` WRITE;
/*!40000 ALTER TABLE `tb_course` DISABLE KEYS */;
INSERT INTO `tb_course` VALUES ('000001','RFID技术原理与应用',4,64,'必修','计算机'),('000002','go语言程序设计',2.5,32,'公选','计算机学院'),('000003','机器学习',3,48,'专选','计算机学院'),('000004','数据结构',4,64,'必修','计算机学院');
/*!40000 ALTER TABLE `tb_course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_dean`
--

DROP TABLE IF EXISTS `tb_dean`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_dean` (
  `Dno` char(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '系主任职工编号',
  `Dname` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '系主任姓名',
  `Dsex` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT '系主任性别',
  `Dbirthday` date NOT NULL COMMENT '系主任出生日期',
  `Ddept` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '系主任所属院系',
  `Dphone` varchar(11) COLLATE utf8_unicode_ci NOT NULL COMMENT '系主任联系电话',
  `Dpassword` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '系主任登录密码',
  `Dclass` varchar(45) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '职称',
  PRIMARY KEY (`Dno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_dean`
--

LOCK TABLES `tb_dean` WRITE;
/*!40000 ALTER TABLE `tb_dean` DISABLE KEYS */;
INSERT INTO `tb_dean` VALUES ('000003','系主任','男','1997-08-12','计算机','1234567','1','教授');
/*!40000 ALTER TABLE `tb_dean` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_stucourse`
--

DROP TABLE IF EXISTS `tb_stucourse`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_stucourse` (
  `Cnumber` char(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '课堂编号',
  `Sno` char(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '学生学号',
  PRIMARY KEY (`Sno`,`Cnumber`),
  KEY `tb_stucourse_ibfk_1` (`Cnumber`),
  CONSTRAINT `tb_stucourse_ibfk_2` FOREIGN KEY (`Sno`) REFERENCES `tb_student` (`Sno`),
  CONSTRAINT `tb_stucourse_ibfk_3` FOREIGN KEY (`Cnumber`) REFERENCES `tb_classinfo` (`Cnumber`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_stucourse`
--

LOCK TABLES `tb_stucourse` WRITE;
/*!40000 ALTER TABLE `tb_stucourse` DISABLE KEYS */;
INSERT INTO `tb_stucourse` VALUES ('000002','S00001'),('000002','S00004'),('000003','S00001'),('000003','S00004'),('0001','S00001'),('0001','S00004');
/*!40000 ALTER TABLE `tb_stucourse` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_student`
--

DROP TABLE IF EXISTS `tb_student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_student` (
  `Sno` char(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '学号',
  `Smajor` char(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '专业',
  `Sname` varchar(20) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '名字',
  `Ssex` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT '性别',
  `Sbirthday` date NOT NULL COMMENT '出生日期',
  `Spassword` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '密码',
  `Sclass` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '班级',
  `Sphone` varchar(20) CHARACTER SET utf8 NOT NULL COMMENT '联系方式\n',
  PRIMARY KEY (`Sno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_student`
--

LOCK TABLES `tb_student` WRITE;
/*!40000 ALTER TABLE `tb_student` DISABLE KEYS */;
INSERT INTO `tb_student` VALUES ('S00001','物联网','赵敏','女','1999-05-01','2','1601','123456'),('S00002','信息安全','张无忌','男','1999-01-01','1','1601','123456'),('S00003','计算机科学与技术','张三丰','男','1997-12-12','2','1602','123456'),('S00004','计算机科学与技术','杨消','男','1998-01-01','1','1603','');
/*!40000 ALTER TABLE `tb_student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_teacher`
--

DROP TABLE IF EXISTS `tb_teacher`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_teacher` (
  `Tno` char(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '教师职工编号',
  `Tname` varchar(20) CHARACTER SET utf8 NOT NULL COMMENT '教师姓名',
  `Tsex` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT '教师性别',
  `Tbirthday` date NOT NULL COMMENT '教师出生日期',
  `Tdept` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '教师所属院系',
  `Tphone` varchar(11) COLLATE utf8_unicode_ci NOT NULL COMMENT '教师联系电话',
  `Tpassword` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '教师登录密码',
  `Tclass` varchar(20) CHARACTER SET utf8 DEFAULT NULL COMMENT '职称',
  PRIMARY KEY (`Tno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_teacher`
--

LOCK TABLES `tb_teacher` WRITE;
/*!40000 ALTER TABLE `tb_teacher` DISABLE KEYS */;
INSERT INTO `tb_teacher` VALUES ('T00001','黄宏','女','1900-01-01','计算机','123456','1','副教授'),('T00002','周时阳','男','1968-07-12','计算机','123456','1','副教授'),('T00003','肖江','男','2000-01-01','计算机学院','123456','','教授');
/*!40000 ALTER TABLE `tb_teacher` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_teacourse`
--

DROP TABLE IF EXISTS `tb_teacourse`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_teacourse` (
  `Cnumber` varchar(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '课堂编号',
  `Tno` char(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '教师职工编号',
  `Cno` varchar(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '课程代码',
  PRIMARY KEY (`Cnumber`),
  KEY `Cno` (`Cno`),
  KEY `Tno` (`Tno`),
  CONSTRAINT `tb_teacourse_ibfk_1` FOREIGN KEY (`Cno`) REFERENCES `tb_course` (`Cno`),
  CONSTRAINT `tb_teacourse_ibfk_2` FOREIGN KEY (`Tno`) REFERENCES `tb_teacher` (`Tno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_teacourse`
--

LOCK TABLES `tb_teacourse` WRITE;
/*!40000 ALTER TABLE `tb_teacourse` DISABLE KEYS */;
/*!40000 ALTER TABLE `tb_teacourse` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_user`
--

DROP TABLE IF EXISTS `tb_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_user` (
  `id` char(6) COLLATE utf8_unicode_ci NOT NULL COMMENT '账号',
  `pwd` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT '密码',
  `identity` int(11) NOT NULL COMMENT '身份',
  `token` varchar(45) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '通信令牌',
  `deadline` varchar(45) CHARACTER SET utf8 DEFAULT NULL COMMENT '时间线\n',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_user`
--

LOCK TABLES `tb_user` WRITE;
/*!40000 ALTER TABLE `tb_user` DISABLE KEYS */;
INSERT INTO `tb_user` VALUES ('000001','2',0,'1561501964000001','1561505564'),('000002','1',1,'1561306876000002','1561310476'),('000003','1',2,'1561502099000003','1561505699'),('S00001','2',0,'1561502606S00001','1561506206'),('S00004','1',1,'1561503080S00004','1561506680'),('T00001','1',1,'1561502273T00001','1561505873'),('T00003','',1,'',''),('U14905','1',0,'1561404467U14905','1561408067');
/*!40000 ALTER TABLE `tb_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Final view structure for view `allclassinfo`
--

/*!50001 DROP VIEW IF EXISTS `allclassinfo`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`aloha`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `allclassinfo` AS select `tb_classinfo`.`Cnumber` AS `Cnumber`,`tb_classinfo`.`Ctime` AS `Ctime`,`tb_classinfo`.`Csession` AS `Csession`,`tb_classinfo`.`Caddress` AS `Caddress`,`tb_classinfo`.`Csum` AS `Csum`,`tb_course`.`Cno` AS `Cno`,`tb_course`.`Cname` AS `Cname`,`tb_teacher`.`Tno` AS `Tno`,`tb_teacher`.`Tname` AS `Tname` from ((`tb_course` join `tb_classinfo`) join `tb_teacher`) where ((`tb_course`.`Cno` = `tb_classinfo`.`Cno`) and (`tb_teacher`.`Tno` = `tb_classinfo`.`Tno`)) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `personalclass`
--

/*!50001 DROP VIEW IF EXISTS `personalclass`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`aloha`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `personalclass` AS select `tb_classinfo`.`Tno` AS `Tno`,`tb_classinfo`.`Cnumber` AS `Cnumber`,`tb_classinfo`.`Cno` AS `Cno`,`tb_course`.`Cname` AS `Cname`,`tb_course`.`Ccredit` AS `Ccredit`,`tb_course`.`Chour` AS `Chour`,`tb_course`.`Ctype` AS `Ctype`,`tb_course`.`Cdept` AS `Cdept`,`tb_classinfo`.`Ctime` AS `Ctime`,`tb_classinfo`.`Csession` AS `Csession`,`tb_classinfo`.`Caddress` AS `Caddress`,`tb_classinfo`.`Csum` AS `Csum` from (`tb_course` join `tb_classinfo`) where (`tb_course`.`Cno` = `tb_classinfo`.`Cno`) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `stuclass`
--

/*!50001 DROP VIEW IF EXISTS `stuclass`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`aloha`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `stuclass` AS select `tb_classinfo`.`Cnumber` AS `Cnumber`,`tb_classinfo`.`Cno` AS `Cno`,`tb_course`.`Cname` AS `Cname`,`tb_course`.`Ccredit` AS `Ccredit`,`tb_course`.`Chour` AS `Chour`,`tb_classinfo`.`Ctime` AS `Ctime`,`tb_classinfo`.`Csession` AS `Csession`,`tb_classinfo`.`Caddress` AS `Caddress`,`tb_teacher`.`Tno` AS `Tno`,`tb_teacher`.`Tname` AS `Tname` from ((`tb_course` join `tb_classinfo`) join `tb_teacher`) where ((`tb_course`.`Cno` = `tb_classinfo`.`Cno`) and (`tb_classinfo`.`Tno` = `tb_teacher`.`Tno`)) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `studentofclass`
--

/*!50001 DROP VIEW IF EXISTS `studentofclass`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`aloha`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `studentofclass` AS select `tb_stucourse`.`Cnumber` AS `Cnumber`,`tb_student`.`Sno` AS `Sno`,`tb_student`.`Sname` AS `Sname`,`tb_student`.`Sclass` AS `Sclass`,`tb_student`.`Smajor` AS `Smajor`,`tb_student`.`Ssex` AS `Ssex` from (`tb_stucourse` join `tb_student`) where (`tb_student`.`Sno` = `tb_stucourse`.`Sno`) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `stupersonalclass`
--

/*!50001 DROP VIEW IF EXISTS `stupersonalclass`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`aloha`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `stupersonalclass` AS select `tb_classinfo`.`Cnumber` AS `Cnumber`,`tb_course`.`Cname` AS `Cname`,`tb_course`.`Ccredit` AS `Ccredit`,`tb_course`.`Chour` AS `Chour`,`tb_classinfo`.`Ctime` AS `Ctime`,`tb_classinfo`.`Csession` AS `Csession`,`tb_classinfo`.`Caddress` AS `Caddress`,`tb_teacher`.`Tname` AS `Tname`,`tb_stucourse`.`Sno` AS `Sno` from (((`tb_course` join `tb_classinfo`) join `tb_teacher`) join `tb_stucourse`) where ((`tb_stucourse`.`Cnumber` = `tb_classinfo`.`Cnumber`) and (`tb_course`.`Cno` = `tb_classinfo`.`Cno`) and (`tb_classinfo`.`Tno` = `tb_teacher`.`Tno`)) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-06-26  6:59:36
