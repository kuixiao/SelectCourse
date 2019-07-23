package tools

import (
	"encoding/json"
	"fmt"
)

func StructToMapViaJson(temp interface{}) (mapFromStruct map[string]string){

	mapFromStruct = make(map[string]string)

	j, err := json.Marshal(temp)
	if err != nil{
		fmt.Println("error when Marshal")
	}
	json.Unmarshal(j, &mapFromStruct)
	for key, value := range mapFromStruct{
		fmt.Println(key, ":" ,value)
	}
	return mapFromStruct
}

//
//func TestTools() {
//	temp1 := model.Tb_student{
//		"111",
//		"assd",
//		"aaaa",
//		"男",
//		"1998-02-09",
//		"1234",
//		"123",
//		"12345",
//	}
//
//	maptemp1 := StructToMapViaJson(temp1)
//
//	for key, value := range maptemp1{
//		fmt.Println(key, ":" ,value)
//	}
//
//	temp2 := model.Tb_teacher{
//		"111",
//		"assd",
//		"男",
//		"aaaa",
//		"1998-02-09",
//			"",
//			"",
//	}
//
//	maptemp2 := StructToMapViaJson(temp2)
//
//	for key, value := range maptemp2{
//		fmt.Println(key, ":" ,value)
//	}
//
//}
//
