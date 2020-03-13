#include "startdialog.hh"

StartDialog::StartDialog(QWidget *parent, int *blocks_amount):
    QDialog(parent),
    layout_(new QVBoxLayout),
    buttons_{},
    blocks_amount_(blocks_amount)
{
    setUp();
    this->setLayout(layout_);
    *blocks_amount_ = BLOCKS_MIN;
}

StartDialog::~StartDialog()
{
    delete layout_;
    for(QPushButton *p : buttons_){delete p;}
}

void StartDialog::editBlockAmount()
{
    bool ok = false;
    int blocks = QInputDialog::getInt(this,
                                      WINDOW_NAME,
                                      "Insert amount of blocks",
                                      *blocks_amount_,
                                      BLOCKS_MIN,
                                      BLOCKS_MAX,
                                      1,
                                      &ok);
    // case dialog was successful
    if(ok){*blocks_amount_ = blocks;}
}

void StartDialog::startGame()
{
    // main knows to continue with game preparations
    done(QDialog::Accepted);
}

void StartDialog::showHighScore()
{
    QMessageBox mbox;
    // fetch highscore and cast it appropriately
    mbox.setText(QString::fromStdString(
                     FileHandler().readFile(HIGH_SCORES_FILENAME,highscore)));
    mbox.setWindowTitle(WINDOW_NAME);
    mbox.exec();
}

void StartDialog::showInstructions()
{
    QMessageBox mbox;
    // fetch text and cast it
    QString help_text = QString::fromStdString(
                 FileHandler().readFile(INSTRUCTIONS_FILENAME,instruction));
    mbox.setText(help_text);
    mbox.setWindowTitle(WINDOW_NAME);
    mbox.exec();
}

void StartDialog::setUp()
{
    this->setWindowTitle(WINDOW_NAME);

    for(int i = 0; i<options::COUNT; i++)
    {
        buttons_[i] = new QPushButton(this);
        buttons_[i]->setText(BUTTON_TEXTS[i]);
        layout_->addWidget(buttons_[i]);
    }
    connect(buttons_[edit_block_amount],&QPushButton::clicked, this, SLOTS[edit_block_amount]);
    connect(buttons_[start], &QPushButton::clicked, this, SLOTS[start]);
    connect(buttons_[highscore_button], &QPushButton::clicked, this, SLOTS[highscore_button]);
    connect(buttons_[instruction_button], &QPushButton::clicked, this, SLOTS[instruction_button]);
}
