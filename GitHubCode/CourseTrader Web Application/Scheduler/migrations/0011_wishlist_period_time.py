# Generated by Django 3.2.7 on 2021-11-28 17:26

import django.contrib.postgres.fields
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Scheduler', '0010_auto_20211128_1643'),
    ]

    operations = [
        migrations.AddField(
            model_name='wishlist',
            name='period_time',
            field=django.contrib.postgres.fields.ArrayField(base_field=models.CharField(max_length=200), blank=True, null=True, size=None),
        ),
    ]