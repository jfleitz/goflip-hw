Create a stack (say 64 positions).

On Push:
If stack is empty, then write to element 1.
Get currentTimeProcessing (SC = stack counter = current time processing)
If push->Time is >0 (not immediate) then enumerate through linked list until push->Time greater than element->Time
Set push->ptr = element->Next
Set element->Next = push->ptr
Set StackDepth++

On Pop (Queue->ptr = FirstElement):
If StackDepth>0
Start At first Element
Loop while SC >= Element->Time
	Process Element
	Set Queue->ptr=Element->Next
	Delete Element
end loop

If last element, then reset the SC to 0 ( so that we don't ever get too high on the time. Maybe even have it so that we trace/debug this).
