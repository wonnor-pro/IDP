# IDP Software Talk

- First Mich competition, 8/12 got 0
- Test 5 times in a row; set your own testing scenario
- Write a programme so that they can test
- Rapid prototyping

## Testing

- Come up with testing programme - capabilities of the devices
- Testing, small pieces, everyday / every update
- Give handy programmes for other ppl to test

## Integration

Avoid problems like: conducting chassis (short-circuit the circuit), metal grabbing claw (magnetic ...) ...
Testing as a whole

## Programming

- Pick the right library, try more libraries.
- Never get stuck in the loops (counting variable, error detector)
```python
count = 0
while (condition) and (count >= MAX_TRAIL):
    statement
    ...
    count += 1
```
- don't generate unnecessary traffic: give information to the motor until something is changed.

## Camera

- Don't rely on it too much.
(Have a wired idea of using the camera to kill the programme)

## Wifi

- Reliable (Own protocol)
- 3 messages a second (probably)

## General Points

- Change one thing at a time
- Redundancy
- Main loop must be short (fast and short)

