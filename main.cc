#include <fstream>
#include <iostream>
#include <vector>

#include "absl/strings/str_format.h"
#include "glog/logging.h"

std::array<uint32_t, 256> kTable;

void FillTable() {
  uint32_t poly = 0xedb88320;
  uint32_t temp = 0;
  for (uint32_t i = 0; i < kTable.size(); ++i) {
    temp = i;
    for (int j = 8; j > 0; --j) {
      if (temp & 1) {
        temp = static_cast<uint32_t>((temp >> 1) ^ poly);
      } else {
        temp >>= 1;
      }
    }
    kTable[i] = temp;
  }
}

uint32_t Crc32(std::vector<uint8_t> data) {
  uint32_t crc = 0xffffffff;
  for (int i = 0; i < data.size(); ++i) {
    uint8_t index = static_cast<uint8_t>((crc & 0xff) ^ data[i]);
    crc = (crc >> 8) ^ kTable[index];
  }
  return ~crc;
}

std::string GenerateCode(uint32_t crc32, char prefix) {
  return absl::StrFormat("CLV-%c-%c%c%c%c%c", prefix, 'A' + (crc32 % 26),
                         'A' + (crc32 >> 5) % 26, 'A' + (crc32 >> 10) % 26,
                         'A' + (crc32 >> 15) % 26, 'A' + (crc32 >> 20) % 26);
}

int main(int argc, char** argv) {
  google::InstallFailureSignalHandler();
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;
  FillTable();

  if (argc == 1) {
    LOG(ERROR) << "Usage: " << argv[0] << "<config-file>";
    LOG(ERROR) << "  config-file: list of filenames to calculate.";
    return 1;
  }

  std::ifstream config_file(argv[1]);
  CHECK(config_file);

  std::string line;
  while (std::getline(config_file, line)) {
    std::ifstream file(line, std::ios::in | std::ios::binary);
    CHECK(file);
    std::vector<uint8_t> contents((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());

    LOG(INFO) << line << ", " << GenerateCode(Crc32(contents), 'U');
  }
  return 0;
}
