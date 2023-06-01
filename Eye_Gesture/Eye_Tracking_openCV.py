import cv2
# Library that helps to open the camera
import mediapipe as mp
# use to detect face of human
import pyautogui
# to detect the cursor



cam = cv2.VideoCapture(0)
#Calling Videocapture of the 0th device
face_mesh = mp.solutions.face_mesh.FaceMesh(refine_landmarks=True) # refine shows detailed landmarks
# As video is continuously running frame after frame
screen_w, screen_h = pyautogui.size()
# get the dimension of the laptop screen
while True:
    _, frame = cam.read() #Syntax
    frame = cv2.flip(frame, 1)
    # We need to flip the camera so our right appers right
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    # It is easier to detect face in colored frame so converting it
    output = face_mesh.process(rgb_frame)
    #calling face_mesh to process rgb frame
    landmark_points = output.multi_face_landmarks
    # print(landmark_points)
    frame_h, frame_w, _ = frame.shape
    # Tell the height and width of frame
    if landmark_points:
    # We just need 1 face
        landmarks = landmark_points[0].landmark
        # I have 4 landmarks on my eye and enumerate, id will pick either one 
        for id, landmark in enumerate(landmarks[474:478]):
            x = int(landmark.x * frame_w)
            y = int(landmark.y * frame_h)
            # print(x, y)
            # Now crate a circle with the coordinates
            cv2.circle(frame, (x,y), 3, (0, 255, 0))
            # cv2.circle( WHERE?, (CENTER), RADIUS, (R, G, B))
            # prints the landmarks of the faces detected x, y cordinate
            if id == 1:
                screen_x = screen_w / frame_w * x
                screen_y = screen_h / frame_h * y
                pyautogui.moveTo(screen_x, screen_y)
        # now for blink we will use left eye
        left = [landmarks[145], landmarks[159]] # it is landmark of up and down of the eye
        for landmark in left:
            x = int(landmark.x * frame_w)
            y = int(landmark.y * frame_h)
            # print(x, y)
            # Now crate a circle with the coordinates
            cv2.circle(frame, (x,y), 3, (0, 255, 255))
        # print(left[0].y, left[1].y)
        # We can check the position of both pointer of left eye
        if(left[0].y - left[1].y) < 0.005:
            # print("click")
            pyautogui.click()
            pyautogui.sleep(1) # wait for 1 second
    cv2.imshow('EYE CONTROLLED MOUSE', frame)
    cv2.waitKey(1)
