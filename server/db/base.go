package db

import (
	"fmt"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
	"time"
	"log"
)

type BaseGorm struct {
	DB *gorm.DB
}

var baseDB *gorm.DB

// 连接数据库并初始化设置(连接数限制，连接保鲜时间等)
// 返回baseDB *gorm.DB作为唯一的基本连接
func (this *BaseGorm) InitDB() {
	fmt.Println("base.go:InitDB()")
	var err error
	this.DB, err = gorm.Open("mysql", "aloha:kuixiao@tcp(localhost:3306)/SelectCourse?charset=utf8")//可以根据情况修改为自己的数据库信息
	if err != nil {
		log.Fatal(err)
		return
	}
	this.DB.SingularTable(true)
	this.DB.DB().SetMaxIdleConns(10)
	this.DB.DB().SetMaxOpenConns(100)
	this.DB.DB().SetConnMaxLifetime(300*time.Second)
	this.DB.LogMode(true)
	baseDB = this.DB
}

// 获取数据库连接
func (this *BaseGorm) GetDB() (DB *gorm.DB) {
	fmt.Println("base.go:GetDB()")
	if baseDB != nil {
		DB = baseDB
	} else {
		log.Fatal("DB not initial.")
		return
	}
	return
}
