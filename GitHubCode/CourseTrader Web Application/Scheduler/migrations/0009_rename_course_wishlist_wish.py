# Generated by Django 3.2.7 on 2021-11-22 17:05

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('Scheduler', '0008_course_wishes'),
    ]

    operations = [
        migrations.RenameField(
            model_name='wishlist',
            old_name='course',
            new_name='wish',
        ),
    ]
