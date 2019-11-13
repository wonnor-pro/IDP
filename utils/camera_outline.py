import cv2
import numpy as np


def contract(img, a):
    '''
    adjusting the contract accoring to given a
    :param img: numpy array
    :param a: contract coefficient
    :return:
    '''
    Output = img * float(a)
    Output[Output > 255] = 255
    Output = np.round(Output)
    Output = Output.astype(np.uint8)

    return Output

def high_pass(img):
    " high-pass filter "
    blur = cv2.GaussianBlur(img, (51, 51), 0)
    filtered = img - blur
    filtered = filtered + 127 * np.ones(img.shape, np.uint8)

    return filtered

def detection(img, contract_co=10, x_range=[500, 1350]):
    outline = draw_contour(img.copy(), contract_co)
    output_img, blocks = locate_mine(img, outline, x_range)

    return output_img, blocks

def draw_contour(img, contract_co=10):
    '''
    :param img: numpy array
    :param contract_co: contract coefficient
    :param draw_color: color of contour you would like to draw
    :return:
    '''

    # Convert to gray img
    gray = img.copy()
    gray = cv2.cvtColor(gray,cv2.COLOR_BGR2GRAY)

    # Enhancing the image
    gray = contract(gray, contract_co)
    # cv2.imshow("gray", gray)
    # cv2.waitKey()

    ret, binary = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)

    # detect contours
    contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    # draw
    new = np.zeros(img.shape, np.uint8)
    new = cv2.drawContours(new, contours, -1, (255, 255, 255), 3)

    # # show
    # cv2.imshow("show_on_img", img)
    # cv2.waitKey(0)

    return new

def locate_mine(img, outline, x_range=[500, 1350]):
    '''
    :param img: numpy array
    :param contract_co: contract coefficient
    :param draw_color: color of contour you would like to draw
    :return:
    '''
    # Convert to binary img
    gray = outline.copy()
    gray = cv2.cvtColor(gray,cv2.COLOR_BGR2GRAY)
    ret, binary = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)

    # detect contours
    contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    # detect mines
    landmine = []
    landmine_x = []

    for i in range(len(contours)):

        top_x, top_y, w, h = cv2.boundingRect(contours[i])
        centre_x = top_x + w / 2
        centre_y = top_y + h / 2
        btm_x = top_x + w
        btm_y = top_y + h

        # choosing the size of contours, width, height, and x location
        if 6 < w < 25 and 6 < h < 25 and top_x > x_range[0] and top_x < x_range[1]:

            # determine if its a new mine

            new_mine = True
            for x_history in landmine_x:
                if abs(x_history - centre_x) < 2:
                    new_mine = False

            if new_mine:

                # add coordinates to the mine list
                landmine.append((centre_x, centre_y))
                landmine_x.append(centre_x)

                # Draw circle on the map
                cv2.circle(img, (int(centre_x), int(centre_y)), 5, (0, 255, 0), 3)

                # Draw rectangle on the map
                cv2.rectangle(img, (top_x, top_y), (btm_x, btm_y), (0, 255, 0), 2)

                # Print location
                print("Landmine detected at ({},{})".format(centre_x, centre_y))

    # Draw the detection region (x range)
    cv2.rectangle(img, (x_range[0], 0), (x_range[1], 1080), (255, 0, 0), 2)

    return img, landmine

def main():

    x_range = [500, 1350]
    contract_coefficient = 10
    snap_shot_test = True
    real_camera_test = False

    if snap_shot_test:
        # Given snapshot
        snap = cv2.imread('../playground/snapshot1.jpg')
        cv2.imshow('snap', snap)
        cv2.waitKey()
        result_img, _ = detection(snap, contract_coefficient, x_range)
        cv2.imshow('Result Img', result_img)
        cv2.waitKey()

    if real_camera_test:
        # Real camera
        cap = cv2.VideoCapture(1)
        while True:
            _, frame = cap.read()
            cv2.imshow('frame', frame)
            result_img, _ = detection(snap, contract_coefficient, x_range)
            cv2.imshow('Result_Img', result_img)

            k = cv2.waitKey(5) & 0xFF
            if k == 27:
                break

if __name__ == "__main__":
    main()