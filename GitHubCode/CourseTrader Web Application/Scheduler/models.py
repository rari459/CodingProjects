from django.db import models
from django.contrib.auth.models import User
from django.contrib.postgres.fields import ArrayField

class Student(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, primary_key=True)
    firstname = models.CharField(max_length=70)
    lastname = models.CharField(max_length=70)
    emailaddress = models.CharField(max_length=140)

    def __str__(self):
        return self.lastname + ", " + self.firstname

class Course(models.Model):
    course_number = models.CharField(max_length=10)
    course_name = models.CharField(max_length=140)
    semester = models.CharField(max_length=25)
    credit_hours = models.IntegerField()
    students = models.ManyToManyField(Student, 
    through='Enrollment', 
    )
    wishes = models.ManyToManyField(Student, related_name="wishes",
    through='WishList', 
    )
    
    def __str__(self):
        return self.course_number

class Enrollment(models.Model):
    student = models.ForeignKey(Student, null=True, on_delete=models.SET_NULL)
    course = models.ForeignKey(Course, on_delete=models.CASCADE)
    period_time = ArrayField(models.CharField(max_length=200), blank=True, null = True,)

class WishList(models.Model):
    student = models.ForeignKey(Student,null=True, on_delete=models.SET_NULL)
    wish = models.ForeignKey(Course, on_delete=models.CASCADE)
    period_time = ArrayField(models.CharField(max_length=200), blank=True, null = True,)
