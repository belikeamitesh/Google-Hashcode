#include<bits/stdc++.h>
using namespace std;

struct Contributor{
    string name;
    bool picked;
    vector<pair<string,int> >skills;
};
struct Project{
    string name;
    int days;
    int score;
    int best_before;
    vector<pair<string,int> >skillsRequired;
};
struct Solution{
    string project;
    vector<string>names;
};
bool compare(Project p1,Project p2)
{
    return -p1.score + p1.days + int(p1.skillsRequired.size()) + p1.best_before < -p2.score + p2.days + int(p2.skillsRequired.size()) + p2.best_before;
}
bool compare2(Contributor c1,Contributor c2)
{
    return (int)c1.skills.size()<(int)c2.skills.size();
}
int main(){
    
    int contributor_count, project_count;

    vector<Contributor>contributor;
    vector<Project>project;
    vector<Solution>solution;

    cin>>contributor_count>>project_count;

    for(int i=0; i<contributor_count; ++i)
    {
        string name;
        int n;
        vector<pair<string,int> >skills;
        cin>>name>>n;
        for(int j=0; j<n; ++j)
        {
            string skill;
            int level;
            cin>>skill>>level;
            skills.push_back({skill, level});
        }
        contributor.push_back({name, false, skills});
    }
    // for(auto i:contributor)
    // {
    //     cout<<i.name<<endl;
    //     for(auto j:i.skills)
    //     {
    //         cout<<j.first<<' '<<j.second<<endl;
    //     }
    // }
    for(int i=0; i<project_count; ++i)
    {
        int days, score, best_before, n;
        string name;
        
        cin>>name>>days>>score>>best_before>>n;
        vector<pair<string,int> >skillsRequired;
        for(int j=0; j<n; ++j)
        {
            string skill;
            int level;
            cin>>skill>>level;
            skillsRequired.push_back({skill, level});
        }
        project.push_back({name, days, score, best_before, skillsRequired});
    }

    sort(project.begin(), project.end(), compare);
    // sort(contributor.begin(), contributor.end(), compare2);
    int curr_day = 0, score=0;

    for(int i=0; i<project_count; ++i)
    {
        vector<string>names;
        int count = 0;
        set<string>picked;
        for(int j=0; j<project[i].skillsRequired.size(); ++j)
        {
            
            
            for(int k=0; k<contributor.size(); ++k)
            {
                int flag = 0;
                for(int l=0; l<(int)contributor[k].skills.size(); l++)
                {

                    string name = contributor[k].skills[l].first;
                    int level = contributor[k].skills[l].second;

                    if(name == project[i].skillsRequired[j].first && level >= project[i].skillsRequired[j].second && picked.find(contributor[k].name) == picked.end())
                    {
                        names.push_back(contributor[k].name);
                        ++count;
                        picked.insert(contributor[k].name);
                        flag = 1;
                        break;
                    }
                }

                if(flag)
                {
                    break;
                }
            }
        }


        if(count == project[i].skillsRequired.size())
        {
            solution.push_back({project[i].name, names});
            curr_day += project[i].days;
            int difference = project[i].best_before - curr_day;
            if(difference>0)
                score += project[i].score;
            else
            {
                score += max(0, project[i].score + difference-1);
            } 
        }
    }
    cout<<solution.size()<<endl;
    for(int i=0; i<solution.size(); ++i)
    {
        cout<<solution[i].project<<endl;
        for(auto k:solution[i].names)
        {
            cout<<k<<' ';
        }
        cout<<endl;
    }
    // cout<<score<<endl;
    return 0;
}