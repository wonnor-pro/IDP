import cv2

cap = cv2.VideoCapture(1) # External(1) Internal(0)
# cap.set(10, 120) # brightness
# cap.set(11, 128) # contrast
# cap.set(12, 160) # saturation
shot = True

while True:
    _, frame = cap.read()
    if (shot):
        print(frame.shape)
        cv2.imwrite('snapshot1.jpg', frame)
        shot = False

    lab = cv2.cvtColor(frame, cv2.COLOR_BGR2LAB)
    cv2.rectangle(frame, (130,0), (1500,1920), (255,0,0), 2)
    cv2.imshow('frame', frame)
    cv2.imshow('LAB', lab)

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break
