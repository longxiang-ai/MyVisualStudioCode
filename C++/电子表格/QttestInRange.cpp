//返回row行，column列的数据
QString Spreadsheet::text(int row, int column) const
{
    Cell *c = cell(row, column);
    if (c)
    {
        return c->text();
    }
    else
    {
        return "";
    }
}

QVector<double> Spreadsheet::textInRange(QString Range) const
{
    if (Range.indexOf(":") == -1) // if there's : in the string, 则为 A1 类型
    {
        int row, colume;
        char temp[5];
        sscanf(Range.toStdString().c_str(), "%[A-Z]%d", temp, &row);
        colume = atoi(temp);
        QVector<double> ret;
        bool ok;
        double tempd = text(row, colume).toDouble(&ok);
        if (ok)
            ret.append(tempd);
        else
            ret.append(0); // 如果转换失败的话返回一个值只有0的double vector
        return ret;
    }
    // Range 的格式 A1:B1
    int leftColume, rightColume, topRow, bottomRow;
    char temp1[5], temp2[5];
    sscanf(Range.toStdString().c_str(), "%[A-Z]%d:%[A-Z]%d", temp1, &topRow, temp2, &bottomRow);
    leftColume = atoi(temp1);
    rightColume = atoi(temp2);
    int columeCount = rightColume - leftColume + 1;
    int rowCount = bottomRow - topRow + 1;
    int len = columeCount * rowCount;
    QVector<double> ret;
    for (int i = 0; i < len; i++)
    {
        bool ok;
        double temp = text(topRow + i / rowCount,
                           leftColume + i % rowCount)
                          .toDouble(&ok);
        if (ok)
            ret.append(temp);
        else
            ret.append(0);
    }

    return ret;
}