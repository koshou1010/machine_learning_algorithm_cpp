#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include "decision_tree.h"

using namespace std;

struct Data
{
    vector<int> attr;
    int label;
};

typedef pair<int, vector<int>> AttrValueItem; // (attrValue,(numClass0, numClass1, numClass2))
struct Attr
{
    int attr;
    vector<AttrValueItem> valueAndNum;
};

struct Node
{
    bool isLeafNode;            // default = false
    int classLabel;             // default = -1
    int attr;                   // choose Node, use to judgment attr
    int attrValue;              // attr value of father Node
    vector<Node*> children;
    Node();
};
Node::Node() : isLeafNode(false), classLabel(-1), attr(-1), attrValue(-1), children(0){}


/*judgment let node split or not, if yes return true*/
pair<bool, int> isLeaf(vector<Data> trainData, vector<int> attrSet)
{
    pair<bool, int> result(false, 0);
    //all of sample in D are class C 
    vector<int> sizeOfPerClass(CLASS_NUM, 0);
    for (auto& data : trainData)
    {
        sizeOfPerClass[data.label]++;
    }
    for (int classLabelIndex = 0; classLabelIndex < sizeOfPerClass.size(); classLabelIndex++)
    {
        if (sizeOfPerClass[classLabelIndex] == trainData.size()) //if same classes
        {
            result.first = true;
            result.second = classLabelIndex;
            return result;
        }
    }

    // if attr set is blank or D sample is sample of A, signed D is the most classes
    if (attrSet.empty())
    {
        result.first = true;
        result.second = max_element(sizeOfPerClass.begin(), sizeOfPerClass.end()) - sizeOfPerClass.begin();
        return result;
    }

    bool allSame = true;
    for (int i = 0; i < attrSet.size(); i++)
    {
        int attrIndex = attrSet[i];
        int anchor = trainData[0].attr[attrIndex];
        for (int j = 1; j < trainData.size(); j++)
        {
            if (trainData[j].attr[attrIndex] != anchor)
            {
                allSame = false;
                return result;
            }
        }
    }
    result.first = true;
    result.second = max_element(sizeOfPerClass.begin(), sizeOfPerClass.end()) - sizeOfPerClass.begin();
    return result;
}

/* Divide training data to different child nodes according to attribute values (attrValue,(selectedData))*/
map<int, vector<Data>> dataPartition(int attrIndex, vector<Data> trainData)
{
    map<int, vector<Data>> subTrainData;
    for (int i = 0; i < trainData.size(); i++)
    {
        int attrValue = trainData[i].attr[attrIndex];
        subTrainData[attrValue].push_back(trainData[i]);
    }
    return subTrainData;
}


/*loading csv file and stored in totalData
At the same time, split classes_num of data, pushback in totalData[0], [1], [2]*/
void readData(const string& filename, vector<vector<Data>>& totalData)
{
    ifstream fin;
    string line;
    vector<Data> dataPerClass;
    int currentLabel = 0;
    char buffer[256] = { 0 };
    fin.open(filename);
    if (!fin.is_open())
    {
        cout << "Failed to open file.\n";
    }
    else
    {
        while (getline(fin, line))
        {
            istringstream sin(line);
            string field;
            Data data;
            data.attr.clear();
            //cout << line << endl;
            while (getline(sin, field, ','))
            {
                if (data.attr.size() < ATTR_SIZE)
                {
                    data.attr.push_back(atoi(field.c_str()));
                }
                else
                {
                    data.label = atoi(field.c_str());
                }    
            }
            if (data.label != currentLabel)
            {
                totalData.push_back(dataPerClass);
                dataPerClass.clear();
                currentLabel++;
            }
            dataPerClass.push_back(data);
            if (fin.peek() == EOF)
            {
                totalData.push_back(dataPerClass);
            }
        }
        cout << "loading csv file was done" << endl;
        fin.close();
    }
}

/* split training set and testing set */
void splitDataset(vector<vector<Data>> totalData, vector<Data>& trainData, vector<Data>& testData) 
{
    for (auto& data : totalData)
    {
        random_shuffle(data.begin(), data.end());
        trainData.insert(trainData.end(), data.begin(), data.begin() + TRAIN_SIZE_PER_CLASS);
        testData.insert(testData.end(), data.begin() + TRAIN_SIZE_PER_CLASS, data.end());
    }
    random_shuffle(trainData.begin(), trainData.end());
    random_shuffle(testData.begin(), testData.end());
    cout <<"training set num:" << trainData.size() << endl;
    cout <<"testing set num:" << testData.size() << endl;
}

/* calculate entropy Ent(D) */
double getEntropy(vector<int> sizePerClass, int total)
{
    double entropy = 0;
    double possibility = 0;
    for (int i = 0; i < sizePerClass.size(); i++)
    {
        possibility = sizePerClass[i] * 1.0 / total;
        if (!possibility)
        {
            continue;
        }
        entropy += (-possibility) * log(possibility) / log(2);
    }
    return entropy;
}




/*ID3 choose the max gain of feature as the greatest split*/
int chooseAttr(vector<Data> trainData, vector<int> attrSet) 
{
    int numTrainData = trainData.size();
    vector<int> sizePerClass(CLASS_NUM, 0);
    for (int i = 0; i < numTrainData; i++)// count num of each classes
    {  
        int label = trainData[i].label;
        sizePerClass[label]++;
    }
    // Although the maximum gain entropy only needs to be solved to minimize the second term, but for the corresponding gain entropy formula, calculate Ent(D)
    double entropy = getEntropy(sizePerClass, numTrainData);
    vector<double> gain(ATTR_SIZE, INT_MIN);// Store the gain entropy of each feature selected, initialized to INT_MIN
    for (auto& attrIndex : attrSet)
    {
        Attr attrValueAndPerSize;
        attrValueAndPerSize.attr = attrIndex;
        for (int j = 0; j < numTrainData; j++)
        {
            int attrValue = trainData[j].attr[attrIndex];
            int label = trainData[j].label;
            bool attrValueExist = false;
            for (auto& attrValueItem : attrValueAndPerSize.valueAndNum)
            {
                if (attrValue == attrValueItem.first)
                {
                    attrValueItem.second[label]++;
                    attrValueExist = true;
                    break;
                }
            }
            // If the attrValue does not exist in attrValueAndPerSize, create and insert
            if (!attrValueExist)
            {
                vector<int> perClassSize(CLASS_NUM, 0);
                perClassSize[label]++;
                pair<int, vector<int>> newItem(attrValue, perClassSize);
                attrValueAndPerSize.valueAndNum.push_back(newItem);
            }
        }
        gain[attrIndex] = entropy;
        for (auto& AttrValueItem : attrValueAndPerSize.valueAndNum)
        {
            int totalNum = 0;
            for (auto& num : AttrValueItem.second)
                totalNum += num;
            gain[attrIndex] -= totalNum * 1.0 * getEntropy(AttrValueItem.second, totalNum) / numTrainData;
        }
    }
    int chosenAttrIndex = max_element(gain.begin(), gain.end()) - gain.begin();
    return chosenAttrIndex;
}



/* build node */
void treeGenerate(Node* root, vector<Data> trainData, vector<int> attrSet)
{
    pair<bool, int> isStop = isLeaf(trainData, attrSet);
    if (isStop.first)       
    {
        root->isLeafNode = true;
        root->classLabel = isStop.second;
        return;
    }
    root->attr = chooseAttr(trainData, attrSet);
    //Remove divided attributes from the attribute set
    for (int i = 0; i < attrSet.size(); i++)
    {
        if (attrSet[i] == root->attr)
        {
            attrSet.erase(attrSet.begin() + i);
            break;
        }
    }
    map<int, vector<Data>> subTrainData = dataPartition(root->attr, trainData);
    auto it = subTrainData.begin();
    while (it != subTrainData.end())
    {
        Node* node = new Node();
        node->attrValue = it->first;
        root->children.push_back(node);
        treeGenerate(node, it->second, attrSet);
        it++;
    }
}

int predict(Node* root, vector<int> data)
{
    cout << "start to predict..." << endl;
    Node* node = root;
    while (node != NULL)
    {
        if (node->isLeafNode)
        {
            return node->classLabel;
        }
        int attrIndex = node->attr;
        for (auto branch : node->children)
        {
            if (branch->attrValue == data[attrIndex])
            {
                //cout << branch->attrValue << " , " << data[attrIndex] << endl;
                node = branch;
                break;
            }
        }
    }

    return -1;
}

double evaluate(Node* root, vector<Data> testData)
{
    int right = 0, wrong = 0; //count right and wrong sample
    int groundTruth = -1, predictResult = -1;
    for (auto data : testData)
    {
        groundTruth = data.label;
        predictResult = predict(root, data.attr);
        cout << predictResult << endl;
        if (groundTruth != predictResult)
        {
            wrong++;
        }
        else
        {
            right++;
        }
    }
    double accuracy = right * 1.0 / (right + wrong);
    return accuracy;
}





int main()
{
    const string dataFileName = "iris_int.csv";
    vector<Data> trainData;
    vector<Data> testData;
    vector<vector<Data>> totalData;
    vector<int> attrSet = {0,1,2,3};
    map<int,vector<Data>> subData;
    readData(dataFileName, totalData);
    splitDataset(totalData, trainData, testData);
    Node* root = new Node();
    treeGenerate(root, trainData, attrSet);
    double accuracy = evaluate(root, testData);
    cout << "accuracy=" << accuracy << endl;

    return 0;
}
