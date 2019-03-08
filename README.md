# BIB_freeRTOS
Bibliotecas para o freeRTOS e o MCU MKL25Z128VLK4 implementadas em C++

# GPIO
  - Biblioteca simples de GPIO;
  - Criação de GPIO facilmente como por exemplo:
  ```cpp
GPIO ledRed(GPIOB, 18U);
```
  - Funcionalidade de setDirection, setValue e getValue;
```cpp
ledRed.setDirection(OUTPUT);
ledRed.setValue(LOW);
```

# I2C
  - Biblioteca com a implementação do protocolo I2C. 
```cpp
I2C i2c(I2Cx, AddressSlave, mult_value, icr_value);
```
  - Valor padrão para mult_value e icr_value:
      - mult = MULT0;
      - icr = ICR_0x14;
  - Metodos de start(), stop(), writeByte(uint8_t data), readByte(), writeRegister(uint8_t registerAddress, uint8_t data) e readRegister(uint8_t registerAddress).
```cpp
i2c.start();
i2c.stop();
i2c.writeByte(0x01);
uint8_t byte = i2c.readByte();
writeRegister(AddressSlave, 0x01);
uint8_t byte = readRegister(0x01);
```

# MMA8451Q
 - Biblioteca com a implementação do acelerometro MMA8451Q. Utilizando a biblioteca de [I2C], já apresentada;
 - Configurações gerais como frequencia, range e resolução do acelerometro.
```cpp
MMA8451Q mma8451q(freq, range, power);
```
 - Onde os valores padrões para freq, range e power são os seguintes:
    - freq = MMA8451Q_FREQUENCY_1_56Hz;
    - range = MMA8451Q_RANGE_2G;
    - power = MMA8451Q_POWER_HIGH_RESOLUTION.
  - Leitura dos dados:
```cpp
uint16_t x = getX();
uint16_t y = getY();
uint16_t z = getZ();
```

# Compatibilidade
 - Todos os códigos utilizados para o freeRTOS nestas bibliotecas podem ser portadas para o BareMetal, preservando somente os endereços de memória.

   [I2C]: <https://github.com/cabralrobert/BIB_freeRTOS/tree/master/I2C_freeRTOS>
