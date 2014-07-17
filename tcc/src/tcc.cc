#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "tc_driver.h"

const int MAX_FILE_NAME = 1024;

int main(const int argc, char *argv[])
{
  int result;
  bool optimize_check = false;
  bool debug_check = false;
  char input_file[MAX_FILE_NAME];
  char output_file[MAX_FILE_NAME];
  char host_name[MAX_FILE_NAME];

  // getoptを使ってオプション処理
  while((result = getopt(argc, argv, "dO")) != -1) {
    switch(result) {
      case 'd':
        debug_check = true;
        break;

      case 'O':
        optimize_check = true;
        break;
    }
  }

  if (argc == optind) {
    std::cerr << "入力ファイルを指定してください\n";
    return 1;
  }

  strcpy(input_file, argv[optind]);

  TC::TC_Driver driver;

  driver.parse(input_file);

  // 関数引数チェック
  driver.func_args_check();

  if (driver.get_semnerrs() == 0) {
    driver.print(debug_check);

    // コードの生成関数を呼び出す
    driver.code_gen(debug_check, optimize_check);
  }

  if (debug_check == true) {
    (driver.getTokenDriver())->debug();
  }

  // if ((driver.getTokenDriver())->lookup_sym("a")) {
  //   std::cout << 1 << std::endl;
  // }

  return 0;
}
