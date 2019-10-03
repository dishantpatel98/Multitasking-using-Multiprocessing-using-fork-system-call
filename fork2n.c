#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>


int main()
{

   int ret,status;

   unsigned long int i=0;
  //block1
  while(i++<5){ //change this with a reasonable condition !!!
   //we are creating 5 children processes and managing 
   //these , from a common parent process 
   ret = fork();
 

   //if fork() system call API fails, due to certain 
   //resource/restrictions, in the OS- it will return -1, 
   //in the parent process context - the parent process
   //code will terminate, using exit(n) - n !=0 ;  
   //the application is said to be unsuccessful,as 
   //multitasking set-up failed 
   //
   //part of block1
   if(ret<0){ 
           //typically, perror() can print an error 
           //string , based on the error code of 
           //the previous system call API 
           perror("error in fork"); 
           printf("the final value of i is %lu\n", i);
         
           //if the parent fails to create a new process, 
           //it will be treated as an error of the 
           //application and exit(1) is invoked 
           //since it is the first error, exit code is 
           //1 - exit() is the termination system call 
           //API which will normally terminate the process
           //and store the exit code passed, in the pd 
           //of the zombie process 
 
           exit(1); 
   }
   //if the fork() system call API is successful, 
   //the fork() system call will complete and 
   //return  a +ve value to the parent process, 
   //which is the pid of the newly created child  process -
 
   //the following block of code will be processed, in 
   //the parent process context only, not in the child
   //process context - to identify the parent context 
   //of execution, we print the process id and parent 
   //process id (parent process of the current process)  
   //part of block1
   if(ret>0){ //this condition  is true, in the parent 
              //context only  
	   printf("I am in parent process context\n"); 
           printf("in parent .. ppid is %lu ...and pid is %lu\n", 
		   getppid(),getpid());	   
	   //
           //
           //job1 , in the parent's context of execution
           //       instance 
           // 
           //++i;     //ok
           //break;

   //in the parent process context, let us continue the job, 
   //as part of the first block of code,which is to 
   //create multiple children processes   
           continue;
   }
   //this block of code executes, in the context of 
   //a child process only and does appropriate job assigned 
   //to this block of code,  in the 
   //context of the child process only
   //if we have multiple children processes, we can 
   //have multiple jobs, in different children processes - 
   //a form of multitasking  
   //we also print pid and ppid of the children processes  
   //block2
   if(ret==0) { 
	   printf("I am in child process context\n"); 
           printf("in child .. ppid is %lu ...and pid is %lu\n", 
		   getppid(),getpid());	   
           //for each child process, we can assign 
           //a different job 	   

           //for i==1, the first instance of the 
           //child process is doing the job 
           //similarly, for other i values, 
           //other instances of the children processes
           //will do their jobs 

           //job of the child - do any work in the child process
	   if(i==1 || i==2) exit(0);
           if(i==3) exit(1);  
           while(1); //we have added a dummy job to each 
                     //child process          
          //exit(0); 
           break;
           //continue;
   }

 }//while

 //this block of code will be executed only by the parent and 
 //parent will reach here only, if it has completed the 
 //first block of code assigned to the parent and 
 //out of the first block of code
   
 //first block does basic work of setting up 
 //multiple children processes !!!

 //the next block of code is one more block of code
 //executed, in the parent context of execution 
//pause(); 
 //block3
 if(ret>0)//this is to check, the current process is 
           //the parent process 
 {
   while(1){ 
//this while(1) is ok - it has been used with a 
//clear purpose
//it will break when a certain condition is true - 
//see below !!! 

//waitpid() is invoked, in the parent context of execution 
//to clean-up the children processes - as part of 
//process management design of Unix/Linux, 
//waitpid() is typically used, in the parent process
//to clean-up terminated/zombie children processes  
//
//waitpid() does not terminate processes, but cleans up 
//terminated children processes - clean-up will delete 
//pd, after collecting termination status information  
//first parameter can be set to -1, if we allow waitpid()
//to clean-up any terminated child process,not a 
//specific child process 

//first parameter can be a +ve value, if we wish to clean-up
//a specific child process 
//in our cases, we will be using -1, for any child process - 
//using -1 is a common case
//
//second parameter is used to collect the termination 
//status of the terminated child process - when waitpid()
//cleans-up a terminated child process,it will collect 
//the termination status code from the pd and fill 
//the second parameter - in this context, p2 is an 
//address/pointer of an user-space variable - this 
//pointer will be used by the system call service 
//routine to copy the termination status from pd, in 
//system-space to the user-space variable   
//last parameter is flags, which we do not use normally, so
//set to 0 
//
//if waitpid() is invoked and a terminated child process 
//is waiting for clean-up, waitpid() will collect the 
//the termination status code and complete the 
//clean-up of the zombie child - delete pd of the 
//terminated child process - foot-print of a terminated
//child process is deleted  
//
//if waitpid() is invoked and currently, there are no 
//terminated children processes, waitpid() will block
//the parent process, until one child process is 
//terminated - once unblocked, it will be scheduled/
//dispatched/executed - it will complete a clean-up 
//and return - waitpid() is a blocking system call 
//API, which may block, for certain scenarios   

    ret = waitpid(-1,&status,0);
    if(ret>0){
//if waitpid() successfully cleans-up a child process, 
//it will collect and copy the status code,in 
//param2 and also return
//a +ve value of the pid of the 
//cleaned-up child process, in ret  
//
//we cannot use termination status code containing  
//termination status and exit code,directly 
//however, we can extract termination status or exit code, 
//using appropriate macros 
//the WIFEXITED(status) returns TRUE, if the child process
//terminated normally
//the WIFEXITED(status) returns FALSE, if the child process
//terminated abnormally/forcibly
 

    if(WIFEXITED(status)) //normal termination of the process
    {

//WEXITSTATUS(status) will provide 0, if the child's
//active application 
//completed successfully and invoked exit(0)
//in this context, application completes successfully and 
//the process terminates normally 
       if(WEXITSTATUS(status) == 0){ //normal and successfull
          printf("normal and successful\n");
       }
//in this case, child's application completed 
//unsuccessfully, process terminated normally 
       else{    //a +ve value ; normal, but not successful 
                //completion of application/job
                
          printf("normal and unsuccessful\n");

       }
    }
//in addition, there can be another case, where
//the child process is forcibly terminated and 
//child's application was unable to complete the job
//such abnormal or forced termination may be 
//due to bugs , in the application or 
//resource problems, in the system  
    else{ //abnormal (did not succeed)
          printf("abnormal and unsuccessful\n");
    }
   }//ret>0
//waitpid() returns -1, when all the children processes
//are cleaned-up and there are no more children 
//processes to clean-up
//in this context, this block of code has completed
//its job and hence terminates the parent process
    if(ret<0) { 
                 exit(0); 
                 //we exit() or break, from the while loop of waitpid() 
                           } //no child is any state for this process
                           //all the children have terminated and 
                           //cleaned-up by the parent process
   } //second while 
  }//if after while loop */

return 0;
   
}

