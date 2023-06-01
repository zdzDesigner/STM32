int main() {
  // 0x40000000 +  0x00020000 + 0x1000 + 0x18
  *(unsigned int *)0x40021018 |= (1 << 4);           // 打开GPIOC时钟
  *(unsigned int *)0x40011004 &= ~(0x0F << (4 * 5)); // 配置输出模式
  *(unsigned int *)0x40011004 |= (1 << (4 * 5));
  *(unsigned int *)0x4001100C &= ~(1 << 13); // 配置输出低电平
  // *(unsigned int *)0x4001100C |= (1 << 13); // 配置输高电平

  int count = 0;
  int i = 0;
  while (1) {
    count = 0;
    if (i == 0) {
      i++;
      *(unsigned int *)0x4001100C &= ~(1 << 13); // 配置输出低电平
    } else {
      i--;
      *(unsigned int *)0x4001100C |= (1 << 13); // 配置输高电平
    }

    while (count < 100000) {
      count++;
    }
  }
}

void SystemInit(void) {}
