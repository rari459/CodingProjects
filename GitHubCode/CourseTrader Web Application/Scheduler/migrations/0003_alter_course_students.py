# Generated by Django 3.2.7 on 2021-10-19 19:58

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Scheduler', '0002_auto_20211019_1944'),
    ]

    operations = [
        migrations.AlterField(
            model_name='course',
            name='students',
            field=models.ManyToManyField(through='Scheduler.Enrolled', to='Scheduler.Student'),
        ),
    ]
