#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QIcon>
#include <QtGui/QFont>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QWidget window;
    window.setWindowTitle("💰 Money Tracker");
    window.resize(350, 250);
    window.setStyleSheet("background-color: #2D2D2D;");
    
    // Create a simple icon programmatically
    QPixmap iconPixmap(64, 64);
    iconPixmap.fill(Qt::transparent);
    
    QPainter painter(&iconPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Draw dollar sign icon
    painter.setBrush(QColor("#BB86FC"));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(8, 8, 48, 48);
    
    painter.setPen(QPen(Qt::black, 4));
    painter.setFont(QFont("Arial", 28, QFont::Bold));
    painter.drawText(iconPixmap.rect(), Qt::AlignCenter, "$");
    
    window.setWindowIcon(QIcon(iconPixmap));
    
    // Create main vertical layout
    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->setSpacing(15);
    layout->setContentsMargins(25, 25, 25, 25);
    
    // Create text input box
    QLineEdit *inputBox = new QLineEdit();
    inputBox->setPlaceholderText(" Enter amount...");
    inputBox->setStyleSheet("font-size: 16px; padding: 10px; border: 2px solid #BB86FC; border-radius: 5px; color: white; background-color: #3D3D3D;");
    
    // Create horizontal layout for operation buttons
    QHBoxLayout *operationLayout = new QHBoxLayout();
    
    // Create operation buttons with dark theme colors
    QPushButton *addButton = new QPushButton("➕ Add");
    QPushButton *subtractButton = new QPushButton("➖ Subtract");
    
    addButton->setStyleSheet("QPushButton { font-size: 14px; padding: 10px 20px; background-color: #BB86FC; color: black; border-radius: 5px; min-width: 100px; }"
                            "QPushButton:hover { background-color: #A36BFC; }");
    
    subtractButton->setStyleSheet("QPushButton { font-size: 14px; padding: 10px 20px; background-color: #03DAC6; color: black; border-radius: 5px; min-width: 100px; }"
                                 "QPushButton:hover { background-color: #00C9B6; }");
    
    // Add buttons with stretchable space to center them
    operationLayout->addStretch();
    operationLayout->addWidget(addButton);
    operationLayout->addWidget(subtractButton);
    operationLayout->addStretch();
    
    // Create horizontal layout for control buttons
    QHBoxLayout *controlLayout = new QHBoxLayout();
    
    // Create control buttons
    QPushButton *resetButton = new QPushButton("🔄 Reset");
    QPushButton *quitButton = new QPushButton("❌ Quit");
    
    resetButton->setStyleSheet("QPushButton { font-size: 14px; padding: 10px 20px; background-color: #CF6679; color: white; border-radius: 5px; min-width: 100px; }"
                              "QPushButton:hover { background-color: #BA5A6B; }");
    
    quitButton->setStyleSheet("QPushButton { font-size: 14px; padding: 10px 20px; background-color: #6200EE; color: white; border-radius: 5px; min-width: 100px; }"
                             "QPushButton:hover { background-color: #5600E8; }");
    
    // Add buttons with stretchable space to center them
    controlLayout->addStretch();
    controlLayout->addWidget(resetButton);
    controlLayout->addWidget(quitButton);
    controlLayout->addStretch();
    
    // Create label to show total
    QLabel *totalLabel = new QLabel("Total: 0.00");
    totalLabel->setAlignment(Qt::AlignCenter);
    totalLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #03DAC6; padding: 20px; border: 3px solid #BB86FC; border-radius: 10px; background-color: #1E1E1E;");
    
    // Add widgets to main layout
    layout->addWidget(inputBox);
    layout->addLayout(operationLayout);
    layout->addLayout(controlLayout);
    layout->addWidget(totalLabel);
    layout->addStretch();
    
    // Variable to store running total
    double total = 0.0;
    
    // Try to load saved total from file
    QFile file("saved_total.txt");
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString saved = in.readAll();
        total = saved.toDouble();
        totalLabel->setText(QString("Total: %1").arg(total, 0, 'f', 2));
        file.close();
    }
    
    // Function to save total to file
    auto saveTotal = [&]() {
        QFile file("saved_total.txt");
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << total;
            file.close();
        }
    };
    
    // Function to update display with 2 decimal places
    auto updateDisplay = [&]() {
        totalLabel->setText(QString("Total: %1").arg(total, 0, 'f', 2));
    };
    
    // Make Add button work when clicked
    QObject::connect(addButton, &QPushButton::clicked, [&]() {
        QString text = inputBox->text();
        bool ok;
        double amount = text.toDouble(&ok);
        
        if (ok && amount > 0) {
            total += amount;
            updateDisplay();
            inputBox->clear();
            saveTotal();
        } else {
            inputBox->setStyleSheet("font-size: 16px; padding: 10px; border: 2px solid #CF6679; border-radius: 5px; color: white; background-color: #3D3D3D;");
            inputBox->setPlaceholderText(" Invalid amount! Try again...");
            inputBox->clear();
        }
    });
    
    // Make Subtract button work when clicked
    QObject::connect(subtractButton, &QPushButton::clicked, [&]() {
        QString text = inputBox->text();
        bool ok;
        double amount = text.toDouble(&ok);
        
        if (ok && amount > 0) {
            total -= amount;
            updateDisplay();
            inputBox->clear();
            saveTotal();
        } else {
            inputBox->setStyleSheet("font-size: 16px; padding: 10px; border: 2px solid #CF6679; border-radius: 5px; color: white; background-color: #3D3D3D;");
            inputBox->setPlaceholderText(" Invalid amount! Try again...");
            inputBox->clear();
        }
    });
    
    // Make Reset button work
    QObject::connect(resetButton, &QPushButton::clicked, [&]() {
        total = 0;
        updateDisplay();
        inputBox->clear();
        saveTotal();
    });
    
    // Make Quit button work
    QObject::connect(quitButton, &QPushButton::clicked, [&]() {
        window.close();
    });
    
    // Reset input box style when user starts typing
    QObject::connect(inputBox, &QLineEdit::textChanged, [&]() {
        inputBox->setStyleSheet("font-size: 16px; padding: 10px; border: 2px solid #BB86FC; border-radius: 5px; color: white; background-color: #3D3D3D;");
        inputBox->setPlaceholderText(" Enter amount...");
    });
    
    window.show();
    return app.exec();
}
