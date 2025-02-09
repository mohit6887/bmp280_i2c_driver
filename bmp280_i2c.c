#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include<linux/spinlock.h>

struct bmp280_dev{
	struct i2c_client *client;
	int frequency;
};


static int bmp280_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int bmp280_remove(struct i2c_client *client);


static int bmp280_probe(struct i2c_client *client , const struct i2c_device_id *id)
{

	printk("bmp280 probe function called \n");
	int ret =-1;
	unsigned long val;

	struct bmp280_dev *bmp280;
	struct device *dev=&client->dev;
	bmp280 =devm_kzalloc(&client->dev,sizeof(struct bmp280_dev),GFP_KERNEL);

	i2c_set_clientdata(client, bmp280);

	bmp280->client=client;
	if(client->addr ==0x76)
	{
		printk(" correct  device attached \n");
	}
/*	u32 frequency;

	ret=device_property_read_u32(dev,"clock-frequency",&frequency);
	if(ret<0)
	{
		printk(" Error cannot red clock frequency\n");
	}
	else
	{
		printk(" frequency read = %d \n",frequency);
	}

*/
	return 0;
}

static int bmp280_remove(struct i2c_client *client)
{
	printk(" I am in the remove function \n");

	return 0;
}
static const struct of_device_id bmp280_dt_ids[]={
	{.compatible="bmp280",},
	{}
};
MODULE_DEVICE_TABLE(of,bmp280_dt_ids);

static const struct i2c_device_id i2c_ids[] =
{
	{.name="bmp280",},
		{}
};
MODULE_DEVICE_TABLE(i2c,i2c_ids);
static struct i2c_driver bmp280_driver = {
	.driver ={
		.name="bmp280",
		.owner=THIS_MODULE,
		.of_match_table=bmp280_dt_ids,
	},
	.probe=bmp280_probe,
	.remove=bmp280_remove,
	.id_table=i2c_ids,
};

module_i2c_driver(bmp280_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MOHIT SHARMA <mohittmyhaoo.com>");
MODULE_DESCRIPTION("lINUX I2C DEVICE DRIVER FOR THE BMP280");



