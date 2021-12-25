from django.forms.fields import NullBooleanField
from django.shortcuts import render, redirect
from .forms import EnrollmentCreationForm, NewUserForm, WishListForm, StudentProfileForm
from django.contrib.auth import login, authenticate, logout
from django.contrib import messages
from django.http import HttpResponse
from .models import Enrollment, Student, Course, WishList
from django.template import context, loader
from django.contrib.auth.forms import AuthenticationForm
from django.shortcuts import render, redirect

def index(request):
    return render(request, 'Scheduler/home.html')

def students(request):
    student_list = Student.objects.order_by('pk')
    template = loader.get_template('Scheduler/students.html')
    context = {
        'student_list' : student_list
        
    }
    return render(request, 'Scheduler/students.html', context)

    #return HttpResponse(template.render(context, request))

def student(request, pk):
    s = Student.objects.get(pk=pk)
    course_list = s.enrollment_set.all()
    schedule = []
    for enroll in course_list:
        withperiod = (Course.objects.get(pk = enroll.course_id), enroll.period_time)
        schedule.append(withperiod)
   
    courses = []
    wishlist = s.wishlist_set.all()
    for wish in wishlist:
        withperiod = (Course.objects.get(pk = wish.wish_id), wish.period_time)
        courses.append(withperiod)
    context = {
        'course_list' : schedule,
        'courses' : courses,    
    }
    return render(request, 'Scheduler/student.html', context) 
    
def register_request(request):
	if request.method == "POST":
		form = NewUserForm(request.POST)
		student_form = StudentProfileForm(request.POST)
		if form.is_valid() and student_form.is_valid():
			user = form.save()
			profile = student_form.save(commit=False)
			profile.user = user
			profile.save()
			login(request, user)
			messages.success(request, "Registration successful." )
			return redirect("Scheduler:students")
		messages.error(request, "Unsuccessful registration. Invalid information.")
	form = NewUserForm(request.POST)
	student_form = StudentProfileForm(request.POST)
	return render (request=request, template_name="Scheduler/register.html", context={"register_form":form, "student_form":student_form})

def login_request(request):
	if request.method == "POST":
		form = AuthenticationForm(request, data=request.POST)
		if form.is_valid():
			username = form.cleaned_data.get('username')
			password = form.cleaned_data.get('password')
			user = authenticate(username=username, password=password)
			if user is not None:
				login(request, user)
				messages.info(request, f"You are now logged in as {username} {request.user.pk}.")                
				return redirect("Scheduler:student", pk = request.user.pk)
			else:
				messages.error(request,"Invalid username or password.")
		else:
			messages.error(request,"Invalid username or password.")
	form = AuthenticationForm()
	return render(request=request, template_name="Scheduler/login.html", context={"login_form":form})

def logout_request(request):
	logout(request)
	messages.info(request, "You have successfully logged out.") 
	return redirect("Scheduler:index")

def addClass(request, pk):
    enroll_form = EnrollmentCreationForm(request.POST or None, request = request)
    if enroll_form.is_valid():
        enroll_form.save()
        return redirect('Scheduler:student', pk = pk) 
    return render(request=request, template_name="Scheduler/addClass.html", context={"form":enroll_form})


def addWish(request, pk):
    wish_form = WishListForm(request.POST or None, request = request)
    if wish_form.is_valid():
        wish_form.save()
        return redirect('Scheduler:student', pk = pk) 
    return render(request=request, template_name="Scheduler/addWish.html", context={"form":wish_form})


def pairing(request, pk):
    pairing = []
    s = Student.objects.get(pk=pk)
    wishes = []
    wishlist = s.wishlist_set.all()
    
    total = Student.objects.exclude(pk=pk)
    
    for wish in wishlist:
        for student in total:
            e = student.enrollment_set.all()
            for enroll in e:
                if wish.wish_id == enroll.course_id and wish.period_time == enroll.period_time and wish.period_time != None:
                    pair = (Student.objects.get(pk = enroll.student_id), Course.objects.get(pk = enroll.course_id), enroll.period_time)
                    pairing.append(pair)

    context = {
        'pairing' : pairing,    
    }
    return render(request, 'Scheduler/pairing.html', context) 