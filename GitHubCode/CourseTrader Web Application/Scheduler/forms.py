from django import forms
from django.forms import ModelForm, TextInput, EmailInput
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User
from .models import Course, Enrollment, Student, WishList
from django.contrib.postgres.fields import ArrayField


class NewUserForm(UserCreationForm):
	class Meta:
		model = User
		fields = ("username", "password1", "password2")

class StudentProfileForm(forms.ModelForm):
	class Meta:
		model = Student
		fields = ('firstname', 'lastname', "emailaddress")

class EnrollmentCreationForm(ModelForm):
	course = forms.ModelChoiceField(queryset=Course.objects.all())
	period_time = ArrayField((forms.CharField(max_length=100, required=False)))
	class Meta:
		model = Enrollment
		fields = [
			"student", "course", "period_time"
		]

	def __init__(self, *args, **kwargs):
		self.request = kwargs.pop("request")
		super(EnrollmentCreationForm, self).__init__(*args, **kwargs)
		self.fields['student'].queryset = Student.objects.filter(pk= self.request.user.pk)
		self.fields['student'].empty_label = None
	
class WishListForm(ModelForm):
	wish = forms.ModelChoiceField(queryset=Course.objects.all())
	period_time = ArrayField((forms.CharField(max_length=100, required=False)))

	class Meta:
		model = WishList
		fields = [
			"student", "wish", "period_time",
		]

	def __init__(self, *args, **kwargs):
		self.request = kwargs.pop("request")
		super(WishListForm, self).__init__(*args, **kwargs)
		self.fields['student'].queryset = Student.objects.filter(pk= self.request.user.pk)
		self.fields['student'].empty_label = None