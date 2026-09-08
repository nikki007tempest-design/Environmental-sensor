#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>

/* Thingy:53 RGB LED - using Green LED */
#define LED_RED_NODE    DT_ALIAS(led0)
#define LED_GREEN_NODE  DT_ALIAS(led1)
#define LED_BLUE_NODE   DT_ALIAS(led2)

static const struct gpio_dt_spec led_red   = GPIO_DT_SPEC_GET(LED_RED_NODE, gpios);
static const struct gpio_dt_spec led_green = GPIO_DT_SPEC_GET(LED_GREEN_NODE, gpios);
static const struct gpio_dt_spec led_blue  = GPIO_DT_SPEC_GET(LED_BLUE_NODE, gpios);

static void blink_green(void)
{
    gpio_pin_set_dt(&led_green, 1);
    k_sleep(K_MSEC(200));
    gpio_pin_set_dt(&led_green, 0);
}

int main(void)
{
    /* Initialize LEDs */
    if (!gpio_is_ready_dt(&led_green)) {
        printk("Green LED not ready!\n");
        return -1;
    }
    gpio_pin_configure_dt(&led_red,   GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led_green, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led_blue,  GPIO_OUTPUT_INACTIVE);

    /* Initialize sensor */
    const struct device *dev = DEVICE_DT_GET_ONE(bosch_bme680);
    if (!device_is_ready(dev)) {
        printk("BME688 sensor not ready!\n");
        return -1;
    }

    printk("BME688 Temperature Reader started\n");

    while (1) {
        struct sensor_value temp, humidity, pressure;

        int ret = sensor_sample_fetch(dev);
        if (ret) {
            printk("Failed to fetch sensor data: %d\n", ret);
            /* Blink RED on error */
            gpio_pin_set_dt(&led_red, 1);
            k_sleep(K_MSEC(200));
            gpio_pin_set_dt(&led_red, 0);
            k_sleep(K_MSEC(2000));
            continue;
        }

        sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
        sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);
        sensor_channel_get(dev, SENSOR_CHAN_PRESS, &pressure);

        printk("Temperature : %d.%02d C\n", temp.val1, temp.val2 / 10000);
        printk("Humidity     : %d.%02d %%\n", humidity.val1, humidity.val2 / 10000);
        printk("Pressure     : %d.%02d kPa\n", pressure.val1, pressure.val2 / 10000);
        printk("-------------------------------------------\n");

        /* Blink GREEN on successful sample */
        blink_green();
        k_sleep(K_MSEC(2000));
    }

    return 0;
}
