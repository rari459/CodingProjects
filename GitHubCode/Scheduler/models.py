from django.db import models
from django.contrib.postgres.fields import ArrayField

class Course(models.Model):
    course_number = models.CharField(max_length=10)
    course_name = models.CharField(max_length=140)
    semester = models.CharField(max_length=25)
    credit_hours = models.IntegerField()

    def __str__(self):
        return self.course_number


class Period(models.Model):
    course = models.ForeignKey(Course, on_delete=models.CASCADE)
    period_time = ArrayField(models.CharField(max_length=200), blank=True)

    def __str__(self):
        return str(self.period_time)
