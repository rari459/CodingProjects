from django.contrib import admin
from django.contrib.auth.admin import UserAdmin
from django.forms import ModelForm
from .models import Course, Student, Enrollment, User, WishList


class enrollments_inline(admin.TabularInline):
    model = Enrollment
    extra = 1

class wishlist_inline(admin.TabularInline):
    model = WishList
    extra = 1

class CourseAdmin(admin.ModelAdmin):
    fieldsets = [
        (None, {'fields': ['course_number']}),
        (None, {'fields': ['course_name']}),
        (None, {'fields': ['semester']}),
        (None, {'fields': ['credit_hours']}),
    ]
    inlines = (enrollments_inline,) 


class StudentAdmin(admin.ModelAdmin):
   fieldsets = [
       (None, {'fields': ['firstname']}),
       (None, {'fields': ['lastname']}),
       (None, {'fields': ['emailaddress']}),
   ]
   inlines = (enrollments_inline, wishlist_inline)

class StudentForm(ModelForm):
    def __init__(self, *args, **kwargs):
        super(StudentForm, self).__init__(*args, **kwargs)
        if self.instance.pk is None:
            self.empty_permitted = False # Here

    class Meta:
        model = Student
        fields = '__all__'
        exclude = ()

class StudentinLine(admin.TabularInline):
    model = Student
    form = StudentForm

class UserAdmin(UserAdmin):
    inlines = [StudentinLine, ]

admin.site.register(Course, CourseAdmin)
admin.site.register(Student, StudentAdmin)
admin.site.unregister(User)
admin.site.register(User, UserAdmin)

