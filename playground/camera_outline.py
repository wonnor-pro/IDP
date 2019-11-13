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

def locate_mine(original, img, x_range=[500, 1350]):
    '''
    :param img: numpy array
    :param contract_co: contract coefficient
    :param draw_color: color of contour you would like to draw
    :return:
    '''
    # Convert to gray img
    gray = img.copy()
    gray = cv2.cvtColor(gray,cv2.COLOR_BGR2GRAY)

    ret, binary = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)

    # detect contours
    contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    # detect mines
    blocks = []

    for i in range(len(contours)):
        x, y, w, h = cv2.boundingRect(contours[i])
        # choosing the size of contours, width, height, and x location
        if 6 < w < 25 and 6 < h < 25 and x > x_range[0] and x < x_range[1]:

            # add coordinates to the mine list
            blocks.append((x + w / 2, y + h / 2))

            # Draw circle on the map
            cv2.circle(original, (int(x + w / 2), int(y + h / 2)), 5, (0, 255, 0), 3)

            # Draw rectangle on the map
            cv2.rectangle(original, (x, y), (x + w, y + h), (0, 255, 0), 2)

            # Print location
            print("Block detected at ({},{})".format(x + w / 2, y + h / 2))

    # Draw the detection region (x range)
    cv2.rectangle(original, (x_range[0], 0), (x_range[1], 1080), (255, 0, 0), 2)

    return original, blocks

def main():
    # Given snapshot
    snap = cv2.imread('snapshot.jpg')
    cv2.imshow('snap', snap)
    cv2.waitKey()
    outline, _ = detection(snap, 10, [500,1350])
    cv2.imshow('Outline', outline)
    cv2.waitKey()

    # Real camera
    cap = cv2.VideoCapture(1)
    while True:
        _, frame = cap.read()
        cv2.imshow('frame', frame)
        outline, _ = detection(snap, 10, [500,1350])
        cv2.imshow('Outline', outline)

        k = cv2.waitKey(5) & 0xFF
        if k == 27:
            break

if __name__ == "__main__":
    main()