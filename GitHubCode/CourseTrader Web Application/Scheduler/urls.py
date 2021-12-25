from django.urls import path

from . import views
app_name = 'Scheduler'
urlpatterns = [
    path('', views.index, name='index'),
    path('students/', views.students, name='students'),
    path('students/<int:pk>/', views.student, name='student'),
    path("register/", views.register_request, name = "register"),
    path("login/", views.login_request, name = "login"),
    path('addclass/<int:pk>/', views.addClass, name = "addclass"),
    path('addwish/<int:pk>/', views.addWish, name = "addwish"),
    path('pairing/<int:pk>/', views.pairing, name = "pairing"),
    path("logout/", views.logout_request, name= "logout"),
]