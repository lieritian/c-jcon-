#include <stdio.h>
#include "cJSON.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
 
int main()
{
	//打开保存JSON数据的文件 
	int fd = open("data.json",O_RDWR);
	if(fd < 0)
	{
		perror("open fail\n");
		return -1;
	}
		
	//读取文件中的数据 
	char buf[2048] = {0};
	int ret = read(fd, buf, sizeof(buf));
	if(ret == -1)
	{
		perror("read error");
		return -1;
	}
	
	//关闭文件
	close(fd);
	
	//把该字符串数据转换成JSON数据  (对象)
	cJSON *root=cJSON_Parse(buf);
	if(root == NULL)
	{
		printf("parse error\n");
		return -1;
	}
	
	//根据key值去获取对应的value 
	cJSON *value = cJSON_GetObjectItem(root,"time");
	if(value == NULL)
	{
		printf("GetObjectItem error\n");
		return -1;
	}
	//把数据转成 字符串输出  
	char  *date = cJSON_Print(value);
	printf("time=%s\n",date);
	
	//获取数组对象 
	//当前的value 是一个数组对象
	value = cJSON_GetObjectItem(root,"forecast");
	if(value == NULL)
	{
		printf("GetObjectItem error\n");
		return -1;
	}
	
	//获取该数组对象的大小
	int len = cJSON_GetArraySize(value);
	printf("元素个数len=%d\n",len);
	
	//根据下标获取对象   取出第0项
	int i = 0;
	cJSON * type_value = NULL;
	cJSON * date_value = NULL;
	cJSON * date2_value = NULL;
	for(i=0;i<len;i++)
	{
		
		date_value = cJSON_GetArrayItem(value,i);
		type_value = cJSON_GetArrayItem(value,i);
		date2_value = cJSON_GetArrayItem(value,i);
		//获取KEY对应的value 
		date_value = cJSON_GetObjectItem(date_value,"设备IP");
		type_value = cJSON_GetObjectItem(type_value,"用户名");
		date2_value = cJSON_GetObjectItem(date2_value,"密码");
		
		if(date_value == NULL || type_value == NULL  || date2_value ==NULL )
		{
			printf("GetObjectItem error\n");
			return -1;
		}
		
		//获取完毕后转换打印  date = cJSON_Print(date_value);
		printf("%s\t%s\%s\n", cJSON_Print(date_value),cJSON_Print(type_value),cJSON_Print(date2_value));
		
	}
	
	return -1;
	
}