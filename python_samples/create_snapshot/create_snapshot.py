def eightdays(): 
		import datetime
		from datetime import timedelta
		tod = datetime.datetime.now()
		sub = datetime.timedelta(days = 8)
		to_del = tod - sub
		eight_days = (to_del.strftime("%Y-%m-%d"))
		return eight_days

def lambda_handler(event, context):
	import boto3
	import pprint
	import time
	import os

	## dd/mm/yyyy format
	date = (time.strftime("%Y-%m-%d"))

	instance_id = os.environ['instance_id']

	print ("creating image for " + instance_id)

	ec2 = boto3.resource('ec2')

	instance = ec2.Instance(instance_id)

	response = instance.create_image(
    	Description = "www-wordpress-app-backup",
    	Name = "www-wordpress-app-backup-" + date,
    	NoReboot = True
	)

	print ("wordpress image created")

	eightdaysago = "www-wordpress-app-backup-" + eightdays()


	client = boto3.client('ec2')

	#image_name = "www-wordpress-app-backup-" + date
	image_name = eightdaysago

	print ("searching for image named " + image_name)

	response = client.describe_images(
    	Filters=[
        	{
            	'Name': 'name',
            	'Values': [
                	image_name
            	]
        	}
    	]
    )

	if response['Images']:
		image_id = response['Images'][0]['ImageId']
		print ("de-registering image id " + image_id)
		image = ec2.Image(image_id)
		image.deregister()

	else: 
		print("Image " + image_name + " not found.")


	return 0
