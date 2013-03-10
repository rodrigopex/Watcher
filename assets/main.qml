import bb.cascades 1.0

Page {
    Container {
        id: stage
        layout: AbsoluteLayout {
        }
        function closeEye() {
            closingEye.play()
            _controller.moving.connect(stage.openEye)
            console.log("closing")
        }
        function openEye() {
            openingEye.play()
            _controller.moving.disconnect(stage.openEye)
            console.log("opening")
        }
        ImageView {
            imageSource: "images/olho.png"
        }
        ImageView {
            imageSource: "images/iris.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 465
                positionY: 120
            }
        }
        ImageView {
            id: eyes
            imageSource: "images/pupila.png"
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 165
                positionY: -470
            }
            animations: [
                TranslateTransition {
                    id: openingEye
                    fromY: 0
                    toY: -470
                    duration: 500
                },
                TranslateTransition {
                    id: closingEye
                    fromY: -470
                    toY: 0
                    duration: 2000
                }
            ]
        }
        ImageView {
            imageSource: "images/pele.png"
            gestureHandlers: [
                TapHandler {
                    onTapped: {
                        stage.closeEye()
                        closingEye.play()
                    }
                }
            ]
        }
    }
}
