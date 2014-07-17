#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "tc_driver.h"

const int MAX_FILE_NAME = 1024;

int main(const int argc, char *argv[])
{
  int result;
  bool input_check = false;
  bool output_check = false;
  bool debug_check = false;
  bool host_check = false;
  char input_file[MAX_FILE_NAME];
  char output_file[MAX_FILE_NAME];
  char host_name[MAX_FILE_NAME];

  // getoptを使ってオプション処理
  while((result = getopt(argc, argv, "di:o:h:")) != -1) {
    switch(result) {
      case 'd':
        debug_check = true;
        break;

      case 'i':
        input_check = true;
        strcpy(input_file, optarg);
        break;

      case 'o':
        output_check = true;
        strcpy(output_file, optarg);
        break;

      case 'h':
        host_check = true;
        strcpy(host_name, optarg);
        break;
    }
  }

  if (input_check == false) {
    std::cerr << "入力ファイルを指定してください\n";
    return 1;
  }
  if (output_check == false && debug_check == false) {
    std::cerr << "出力ファイルを指定してください\n";
    return 1;
  }


  TC::TC_Driver driver;

  driver.parse(input_file);

  // 関数引数チェック
  driver.func_args_check();

  if (driver.get_semnerrs() == 0) {
    driver.print(debug_check);

    // コードの生成関数を呼び出す
    driver.code_gen(output_file, debug_check);
  }

  if (debug_check == true) {
    (driver.getTokenDriver())->debug();
  }

  // if ((driver.getTokenDriver())->lookup_sym("a")) {
  //   std::cout << 1 << std::endl;
  // }

  return 0;
}
