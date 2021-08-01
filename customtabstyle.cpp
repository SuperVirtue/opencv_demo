#include "customtabstyle.h"
#include <QStyleOptionTab>

CustomTabStyle::CustomTabStyle()
{

}

QSize CustomTabStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const
{
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == QStyle::CT_TabBarTab) {
        s.transpose();
        s.rwidth() = 100; // 设置每个tabBar中item的大小
        s.rheight() = 40;
    }
    return s;
}

void CustomTabStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if (element == CE_TabBarTabLabel) {
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
            QRect allRect = tab->rect;

            if (tab->state & QStyle::State_Selected) {  //选中状态：tab的Qlabel为矩形，底色为白色，边框淡灰色，文字为淡蓝色且加粗居中（具体颜色值由拾色器提取）
                painter->save();
                painter->setPen(0xdadbdc);  //设置item的边框颜色
                painter->setBrush(QBrush(0xcce8ff));  //设置选择之后item的底色
                painter->drawRect(allRect.adjusted(0,0,0,0));  //重绘tab的矩形边框
                painter->restore();  //还原为默认

                painter->save();
                painter->setPen(0x6678d7);  //设置选中后item字的颜色，画笔颜色为淡蓝色
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);  //设置文字居中
                painter->setFont(QFont("", 9, QFont::Bold));  //设置文字样式，大小为9并加粗，颜色由画笔决定
                painter->drawText(allRect, tab->text, option);  //重绘文字
                painter->restore();
            }
            else if(tab->state & QStyle::State_MouseOver) { //悬停状态：tab的Qlabel为矩形，底色为灰色，边框仍未淡灰色，文字加粗居中
                painter->save();
                painter->setPen(0xdadbdc);  //设置悬停时的边框颜色，画笔颜色为淡灰色
                painter->setBrush(QBrush(0xa6a6a6));  //设置悬停时的item背景底色，画刷为灰色
                painter->drawRect(allRect.adjusted(0,0,0,0));  //重绘tab的矩形边框
                painter->restore();  //还原

                painter->save();
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);  //设置文字居中
                painter->setFont(QFont("", 9, QFont::Bold));  //设置文字样式，大小为9并加粗，颜色由画笔决定
                painter->drawText(allRect, tab->text, option);  //重绘文字
                painter->restore();
            }
            else //其它的：tab的Qlabel为矩形，底色为灰色，边框为淡灰色不变，文字不加粗但居中
            {
                painter->save();
                painter->setPen(0xdadbdc);//设置没选中的item边框颜色
                painter->setBrush(QBrush(0xf2f2f2));//设置没选中的item背景底色
                painter->drawRect(allRect.adjusted(0,0,0,0));
                painter->restore();

                painter->save();
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                painter->drawText(allRect, tab->text, option);
                painter->restore();
            }

            return;
        }
    }

    if (element == CE_TabBarTab) {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}
