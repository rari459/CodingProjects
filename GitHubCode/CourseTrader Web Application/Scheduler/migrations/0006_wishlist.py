# Generated by Django 3.2.7 on 2021-11-20 22:21

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('Scheduler', '0005_auto_20211026_1657'),
    ]

    operations = [
        migrations.CreateModel(
            name='WishList',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('course', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='Scheduler.course')),
                ('student', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='Scheduler.student')),
            ],
        ),
    ]
