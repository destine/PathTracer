//Debugging
#include <iostream>
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>

//Debugging segfaults. Copied from stackoverflow from user tgamblin
//http://stackoverflow.com/questions/77005/how-to-generate-a-stacktrace-when-my-gcc-c-app-crashes/77336#77336
void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}