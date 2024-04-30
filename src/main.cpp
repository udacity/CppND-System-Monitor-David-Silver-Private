#include "linux_system.h"
#include "ncurses_display.h"

int main() {
  auto system = LinuxSystem();
  NCursesDisplay::Display(system);
}