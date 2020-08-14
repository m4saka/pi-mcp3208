# rpi-mcp3208
MCP3208 A/D converter imprementation for Raspberry Pi using wiringPi

## Compilation
```
$ git clone https://github.com/m4saka/rpi-mcp3208.git
$ cd rpi-mcp3208
$ make
```

## Usage
Note: Make sure to enable SPI features in `raspi-config` before using.
```
$ ./rpi_mcp3208
```

- Pin number (BCM):
    - CLK: 11
    - DIN: 10
    - DOUT: 9
    - CS(CH0): 8
    - CS(CH1): 7

- Example:
  ```
  << SPI Channel 0 >>
  CH0: 3.2879 [V] (Raw:4081)
  CH1: 0.6010 [V] (Raw:746)
  CH2: 0.1434 [V] (Raw:178)
  CH3: 0.4431 [V] (Raw:550)
  CH4: 0.4262 [V] (Raw:529)
  CH5: 0.1281 [V] (Raw:159)
  CH6: 0.4431 [V] (Raw:550)
  CH7: 0.2425 [V] (Raw:301)

  << SPI Channel 1 >>
  CH0: 0.0000 [V] (Raw:0)
  CH1: 0.0000 [V] (Raw:0)
  CH2: 0.0000 [V] (Raw:0)
  CH3: 0.0000 [V] (Raw:0)
  CH4: 0.0000 [V] (Raw:0)
  CH5: 0.0000 [V] (Raw:0)
  CH6: 0.0000 [V] (Raw:0)
  CH7: 0.0000 [V] (Raw:0)
  ```
