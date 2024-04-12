#include "ncurses_display.h"
#include "linux_system.h"

int main() {
  auto system = LinuxSystem();
  NCursesDisplay::Display(system);
}