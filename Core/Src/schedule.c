/*
 * schedule.c
 *
 *  Created on: Nov 8, 2022
 *      Author: tan
 */
#include "schedule.h"

typedef struct{
	void (*pTask)();
	uint32_t 	Delay;
	uint32_t 	Period;
	uint32_t 	RunMe;
	uint32_t 	TaskID;
}sTasks;
/*
typedef struct Node{
	sTasks task;
	Node* next;
}Node;
*/
unsigned int Error_code_G = 0;

sTasks SCH_tasks_G[SCH_MAX_TASKS];

uint8_t current_index_task = 0;

uint8_t passed_time_since_last_task = 0;

void SCH_Sort_Tasks(){
	sTasks key;
	int j;
	if(current_index_task < 2){
		return;
	}
	for(int  i = 0; i < current_index_task; i++){
		key = SCH_tasks_G[i];
		j = i-1;
		while(j>=0 && SCH_tasks_G[j].Delay > key.Delay){
			SCH_tasks_G[j+1] = SCH_tasks_G[j];
			j--;
		}
		SCH_tasks_G[j+1] = key;
	}
}


void SCH_Init(void){
	current_index_task = 0;
}

unsigned int SCH_Report(){
	return Error_code_G;
}

uint8_t SCH_Delete_Task(uint32_t taskID){
	if(SCH_tasks_G[taskID].pTask == 0x0000){
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
	}
	SCH_tasks_G[taskID].pTask = 0x0000 ;
	SCH_tasks_G[taskID].Delay = 0;
	SCH_tasks_G[taskID].Period = 0;
	SCH_tasks_G[taskID].RunMe = 0;
	for(unsigned int idx=taskID; idx<current_index_task-1; idx++){
		SCH_tasks_G[idx] = SCH_tasks_G[idx+1];
	}
	current_index_task--;
	return 0;
}

uint32_t SCH_Add_Task(void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
	uint8_t temp;
	if(current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period =  PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;
		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		current_index_task++;
		temp = SCH_tasks_G[current_index_task].TaskID;
		SCH_Sort_Tasks();
	}
	return temp;
}

void SCH_Dispatch_Tasks(void){
	sTasks backup;
	if(SCH_tasks_G[0].Delay==0){
		(*SCH_tasks_G[0].pTask)();
		backup = SCH_tasks_G[0];
		for(int i=1; i < current_index_task; i++){
			if(SCH_tasks_G[i].Delay > passed_time_since_last_task){
				SCH_tasks_G[i].Delay = SCH_tasks_G[i].Delay - passed_time_since_last_task;
			}
		}
		passed_time_since_last_task = 0;
		SCH_Delete_Task(0);
		if(backup.Period!=0){
			SCH_Add_Task(backup.pTask, backup.Period, backup.Period);
		}
	}
	return;
}

void SCH_Update(void){
	if(SCH_tasks_G[0].Delay > 0){
		SCH_tasks_G[0].Delay--;
		passed_time_since_last_task++;
	}
	else if(SCH_tasks_G[0].Delay==0){
		SCH_tasks_G[0].RunMe+=1;
		return;
	}
}
