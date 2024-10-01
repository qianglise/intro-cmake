pure function say_hello() result(message)

  implicit none

  character(len=24) :: message

  message = 'Hello world from Fortran'

end function

program hello_world

  implicit none

  character(len=24) :: say_hello

  print *, say_hello()

end program
